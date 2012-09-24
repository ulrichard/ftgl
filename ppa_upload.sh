#!/bin/sh
# build a debian sourcepackage and upload it to the launchpad ppa
for DISTRIBUTION in precise quantal # oneiric natty maverick 
do
	FTGLVERSIONSTR=2.1.3~rc5-9polyextr~${DISTRIBUTION}
	sed -i  -e "s/maverick/${DISTRIBUTION}/g" -e "s/natty/${DISTRIBUTION}/g" -e "s/oneiric/${DISTRIBUTION}/g" -e "s/precise/${DISTRIBUTION}/g" debian/changelog
#	rm -rf debian/source
	dpkg-buildpackage -rfakeroot -k${GPGKEY} -S
	dput ppa:richi-paraeasy/ppa ../ftgl_${FTGLVERSIONSTR}_source.changes
done

