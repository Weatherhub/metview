FROM ubuntu:16.04
LABEL maintainer "Xin Zhang <xin.l.zhang@noaa.gov>"

# install basic tools
RUN apt-get update \
 && apt-get -y upgrade \
 && apt-get install -y --no-install-recommends csh ksh cmake vim bc libblas-dev liblapack-dev libeigen3-dev libfftw3-dev libfftw3-doc libqtwebkit-dev qtbase5-dev  build-essential gfortran flex bison libqt5svg5-dev libqt5xmlpatterns5-dev curl libproj-dev libgdbm-dev imagemagick libnetcdf-dev libpng-dev libcairo2-dev libnetcdf-cxx-legacy-dev libboost-all-dev libpango1.0-dev git libjasper-dev libopenjpeg-dev libncurses5-dev python-pip python-setuptools x11-utils libxml-parser-perl libssl-dev libarmadillo-dev python-dev swig

RUN pip install wheel Jinja2 numpy

# build the common libraries for numerical weather prediction models
WORKDIR /tmp/build
COPY eccodes-2.7.0-Source /tmp/eccodes-2.7.0-Source
COPY odb_api_bundle-0.17.6-Source /tmp/odb_api_bundle-0.17.6-Source
COPY MetviewBundle-2018.02.0-Source /tmp/MetviewBundle-2018.02.0-Source
RUN cd /tmp/build \
    && cmake -DENABLE_NETCDF=ON -DENABLE_JPG=ON -DENABLE_PNG=ON -DENABLE_FORTRAN=ON -DENABLE_AEC=ON -DENABLE_PYTHON=ON ../eccodes-2.7.0-Source \
    && make -j4 \
    && make install \
    && rm -fr  /tmp/build/* \
    && rm -fr ../eccodes-2.7.0-Source \
    && cmake  -DENABLE_PYTHON=ON -DENABLE_FORTRAN=ON -DENABLE_NETCDF=ON -DENABLE_ODB=ON ../odb_api_bundle-0.17.6-Source \
    && make -j4 \
    && make install \
    && rm -fr  /tmp/build/* \
    && rm -fr ../odb_api_bundle-0.17.6-Source \
    && cmake -DENABLE_ODB=ON -DENABLE_ECCODES=ON -DENABLE_QT5=ON -DENABLE_PYTHON=ON -DENABLE_UI=ON ../MetviewBundle-2018.02.0-Source \
    && make -j4 \
    && make install \
    && rm -fr  /tmp/build/* \
    && rm -fr ../MetviewBundle-2018.02.0-Source

WORKDIR /tmp/build
COPY py-ncepbufr /tmp/py-ncepbufr
RUN cd /tmp/py-ncepbufr \
    && python setup.py build \
    && python setup.py install \
    && rm -fr /tmp/py-ncepbufr

ENV HOME /home/metview
RUN    useradd --create-home --home-dir $HOME metview \
    && chown -R metview:metview $HOME

WORKDIR $HOME
USER metview

CMD ["/bin/bash" , "-l"]
