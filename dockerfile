FROM debian:latest

RUN apt-get update && apt-get install -y \
    build-essential \
    devscripts \
    debhelper

WORKDIR /app
COPY . /app

CMD ["bash"]
