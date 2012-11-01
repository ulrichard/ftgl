#!/bin/sh
# build a debian sourcepackage and upload it to the launchpad ppa

:${VERSIONNBR:=$(parsechangelog | grep Version | sed -e "s/Version: //g" -e "s/\\~.*//g")}

for DISTRIBUTION in precise quantal
do
	sed -i -e "s/oneiric/${DISTRIBUTION}/g" -e "s/precise/${DISTRIBUTION}/g" -e "s/quantal/${DISTRIBUTION}/g" debian/changelog
	dpkg-buildpackage -rfakeroot -k${GPGKEY} -S
	dput ppa:richi-paraeasy/ppa ../ftgl_${VERSIONNBR}~${DISTRIBUTION}_source.changes
done

