FROM ubuntu:latest

RUN apt-get update && \
    apt-get install -y build-essential gcc make check libsubunit-dev lcov cppcheck clang-format pkg-config libgtest-dev valgrind

WORKDIR /project

COPY . /project


#RUN make check
RUN make gcov_report
RUN make check
