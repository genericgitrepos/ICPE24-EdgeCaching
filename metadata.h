#ifndef HR_METADATA_H
#define HR_METADATA_H

#include <unordered_map>
#include <set>
#include <string.h>

const double INF = 100.0 * 1000 * 1000;
const int MINIMUM_OBJECTS_COUNT = 100 * 1000 * 1000;

struct HR_ObjectLastSeen {
    int object_id;
    double timestamp;
};

struct HR_ObjectLastSeenCompare {
    bool operator()(const HR_ObjectLastSeen* lhs, const HR_ObjectLastSeen* rhs) const {
        if (lhs->timestamp == rhs->timestamp) {
            return lhs->object_id < rhs->object_id;
        }

        return lhs->timestamp < rhs->timestamp;
    }
};

struct HR_ObjectMetadata {
    double decayed_frequency;
    double* features;
    HR_ObjectLastSeen* last_seen;
};

struct HR_ObjectsMetadata {
    int features_length;
    double decay_factor;
    long long max_objects_count;
    double decayed_frequency;
    std::unordered_map<int, HR_ObjectMetadata*> objects;
    std::set<HR_ObjectLastSeen*, HR_ObjectLastSeenCompare> objects_last_seen;

    HR_ObjectsMetadata(int capacity, int features_length, double decay_factor) {
        this->features_length = features_length;
        this->decay_factor = decay_factor;
        int object_meta_size = sizeof(HR_ObjectMetadata) + sizeof(double) * features_length + sizeof(HR_ObjectLastSeen);
        this->max_objects_count = MINIMUM_OBJECTS_COUNT + capacity / object_meta_size;
        this->decayed_frequency = 0;
    }

    HR_ObjectMetadata* get_metadata(int object_id, int timestamp=0) {
        if (objects.find(object_id) == objects.end()) {
            HR_ObjectMetadata* object_metadata = new HR_ObjectMetadata;
            object_metadata->decayed_frequency = 0;
            object_metadata->features = new double[features_length];
            std::fill(object_metadata->features, object_metadata->features + features_length, INF);
            object_metadata->last_seen = new HR_ObjectLastSeen;
            object_metadata->last_seen->object_id = object_id;
            object_metadata->last_seen->timestamp = timestamp;
            objects[object_id] = object_metadata;
            // objects_last_seen.insert(object_metadata->last_seen);
        }

        return objects[object_id];
    }
    
    void update_features(int object_id, double* features) {
        if (objects.find(object_id) == objects.end()) {
            return;
        }
        
        HR_ObjectMetadata* object_metadata = objects[object_id];
        memcpy(object_metadata->features, features, sizeof(double) * features_length);
    }

    double* get_features(int object_id) {
        if (objects.find(object_id) == objects.end()) {
            return NULL;
        }

        HR_ObjectMetadata* object_metadata = objects[object_id];
        return object_metadata->features;
    }

    double get_decayed_frequency(int object_id) {
        if (objects.find(object_id) == objects.end()) {
            return 0;
        }

        HR_ObjectMetadata* object_metadata = objects[object_id];
        return object_metadata->decayed_frequency / decayed_frequency;
    }

    void seen(int object_id, double timestamp) {
        HR_ObjectMetadata* object_metadata = get_metadata(object_id, timestamp);
        decayed_frequency = decayed_frequency * decay_factor + 1;
        object_metadata->decayed_frequency = object_metadata->decayed_frequency * decay_factor + 1;

        // It's not the first time we see this object
        // if (object_metadata->decayed_frequency != 1) {
        //     objects_last_seen.erase(object_metadata->last_seen);
        //     object_metadata->last_seen->timestamp = timestamp;
        //     objects_last_seen.insert(object_metadata->last_seen);
        // }

        // We have reached the capacity of the metadata
        // if (static_cast<int>(objects.size()) > max_objects_count) {
        //     HR_ObjectLastSeen* last_seen = *objects_last_seen.begin();
        //     HR_ObjectMetadata* tbe_object_metadata = objects[last_seen->object_id];
        //     objects.erase(last_seen->object_id);
        //     objects_last_seen.erase(tbe_object_metadata->last_seen);

        //     delete[] tbe_object_metadata->features;
        //     delete last_seen;
        //     delete tbe_object_metadata;
        // }
    }

    ~HR_ObjectsMetadata() {
        for (auto const& [object_id, object_metadata] : objects) {
            delete[] object_metadata->features;
            delete object_metadata->last_seen;
            delete object_metadata;
        }
    }
};

#endif // HR_METADATA_H