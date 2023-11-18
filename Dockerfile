# Start from a base image with g++ and other necessary build tools
FROM gcc:13.2

# Set the environment variable to noninteractive
ENV DEBIAN_FRONTEND=noninteractive

# Install necessary packages
RUN apt-get update && apt-get upgrade -y
RUN apt-get clean
RUN apt-get install -f
RUN apt-get install -y cmake git libcurl4-openssl-dev

# Change the working directory to /app
WORKDIR /app
COPY makefile /app

# Build the lightgbm
RUN make build_lightgbm

# Copy the 'hr' folder from your local filesystem to the Docker image
COPY include /app/include
COPY hr /app/hr
COPY simulator /app/simulator
RUN mkdir /app/executables
RUN mkdir /app/inputs

# Build the C++ project
RUN make

CMD ./executables/hr