#!/bin/sh
# build a debian sourcepackage and upload it to the launchpad ppa
export GPGKEY=DA94BB53
export DEBEMAIL="richi@paraeasy.ch"
export DEBFULLNAME="Richard Ulrich"
rm -r builddeb
mkdir builddeb
cd builddeb
for DISTRIBUTION in precise # oneiric natty maverick 
do
	FTGLVERSIONSTR=2.1.3~rc5-6polyextr~${DISTRIBUTION}
	sed -i  -e "s/maverick/${DISTRIBUTION}/g" -e "s/natty/${DISTRIBUTION}/g" -e "s/oneiric/${DISTRIBUTION}/g" -e "s/precise/${DISTRIBUTION}/g" debian/changelog
#	rm -rf debian/source
	dpkg-buildpackage -rfakeroot -S
	dput ppa:richi-paraeasy/ppa ../ftgl_${FTGLVERSIONSTR}_source.changes
done

