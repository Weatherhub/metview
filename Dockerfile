FROM ubuntu:16.04
LABEL maintainer "Xin Zhang <xin.l.zhang@noaa.gov>"

# install basic tools
RUN apt-get update \
 && apt-get -y upgrade \
 && apt-get install -y --no-install-recommends csh ksh cmake vim bc libblas-dev liblapack-dev libeigen3-dev libfftw3-dev libfftw3-doc libqtwebkit-dev qtbase5-dev  build-essential gfortran flex bison libqt5svg5-dev libqt5xmlpatterns5-dev curl libproj-dev libgdbm-dev imagemagick libnetcdf-dev libpng-dev libcairo2-dev libnetcdf-cxx-legacy-dev libboost-all-dev libpango1.0-dev git libjasper-dev libopenjpeg-dev libncurses5-dev python-pip python-setuptools x11-utils libxml-parser-perl libssl-dev libarmadillo-dev python-dev swig

RUN pip install wheel Jinja2 numpy pandas

#
# Package URL's
#
ENV ECCODES_URL        https://software.ecmwf.int/wiki/download/attachments/45757960/eccodes-2.7.0-Source.tar.gz
ENV EMOS_URL           https://software.ecmwf.int/wiki/download/attachments/3473472/libemos-4.5.4-Source.tar.gz
ENV ODBAPI_URL         https://software.ecmwf.int/wiki/download/attachments/61117379/odb_api_bundle-0.17.6-Source.tar.gz
ENV METVIEWBUNDLE_URL  https://software.ecmwf.int/wiki/download/attachments/51731119/MetviewBundle-2018.02.0-Source.tar.gz
ENV MAGICS_URL         https://software.ecmwf.int/wiki/download/attachments/3473464/Magics-3.0.2-Source.tar.gz
ENV PYNCEPBUFR_URL     https://github.com/JCSDA/py-ncepbufr.git

#
# build the common libraries for numerical weather prediction models
#
WORKDIR /tmp/build
RUN cd /tmp/build \
#   && echo "Downloading ECCODES from ${ECCODES_URL}" \
#   && curl -SL ${ECCODES_URL} | tar xzC /tmp \
#   && cmake -DENABLE_NETCDF=ON -DENABLE_JPG=ON -DENABLE_PNG=ON -DENABLE_FORTRAN=ON -DENABLE_AEC=ON -DENABLE_PYTHON=ON ../eccodes-2.7.0-Source \
#   && make -j4 \
#   && make install \
#   && rm -fr  /tmp/build/* \
#   && rm -fr ../eccodes-2.7.0-Source \
#   && echo "Downloading EMOS from ${EMOS_URL}" \
#   && curl -SL ${EMOS_URL} | tar xzC /tmp \
#   && cmake ../libemos-4.5.4-Source \
#   && make -j4 \
#   && make install \
#   && rm -fr  /tmp/build/* \
#   && rm -fr ../libemos-4.5.4-Source \
#   && echo "Downloading ODBAPI from ${ODBAPI_URL}" \
#   && curl -SL ${ODBAPI_URL} | tar xzC /tmp \
#   && cmake  -DENABLE_PYTHON=ON -DENABLE_FORTRAN=ON -DENABLE_NETCDF=ON -DENABLE_ODB=ON ../odb_api_bundle-0.17.6-Source \
#   && make -j4 \
#   && make install \
#   && rm -fr  /tmp/build/* \
#   && rm -fr ../odb_api_bundle-0.17.6-Source \
    && echo "Downloading METVIEWBUNDLE from ${METVIEWBUNDLE_URL}" \
    && curl -SL ${METVIEWBUNDLE_URL} | tar xzC /tmp \
    && cmake -DENABLE_EXPOSE_SUBPACKAGES=ON -DCMAKE_INSTALL_PREFIX=/usr/local -DENABLE_ODB=ON -DENABLE_ECCODES=ON -DENABLE_QT5=ON -DENABLE_PYTHON=ON -DENABLE_UI=ON ../MetviewBundle-2018.02.0-Source \
    && make -j4 \
    && make install \
    && rm -fr  /tmp/build/* \
    && rm -fr ../MetviewBundle-2018.02.0-Source \
#   && echo "Downloading MAGICS from ${MAGICS_URL}" \
#   && curl -SL ${MAGICS_URL} | tar xzC /tmp \
#   && cmake  -DENABLE_ODB=ON -Dodb_api_DIR=/usr/local -DENABLE_METVIEW=ON -DENABLE_BUFR=ON -DENABLE_PYTHON=ON -DENABLE_FORTRAN=ON ../Magics-3.0.2-Source \
#   && make -j4 \
#   && make install \
#   && rm -fr  /tmp/build/* \
#   && rm -fr ../Magics-3.0.2-Source

WORKDIR /tmp/build
RUN git clone ${PYNCEPBUFR_URL} \
    && cd /tmp/build/py-ncepbufr \
    && python setup.py build \
    && python setup.py install \
    && cp /tmp/build/py-ncepbufr/src/libbufr.a /usr/local/lib/libbufr.a \
    && rm -fr /tmp/build/*

ENV LD_LIBRARY_PATH /usr/local/lib

ENV HOME /home/metview
RUN    useradd --create-home --home-dir $HOME metview \
    && chown -R metview:metview $HOME

WORKDIR $HOME
USER metview

CMD ["/bin/bash" , "-l"]
