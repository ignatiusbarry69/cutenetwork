TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS += \
    qhttpclient \
    sampleapp


qhttpclient.subdir = qhttpclient
sampleapp.subdir = sampleapp

sampleapp.depends = qhttpclient

