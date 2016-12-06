#FIXME!
default:
	rm -rf bin objs libs
	mkdir -p bin
	mkdir -p objs
	mkdir -p libs
	cd src; make; cd -
	cd src/test; make; cd -