#ifndef UPDATE_H
#define UPDATE_H

class Inotify{
	int fd_;

	Inotify(Inotify const&);
	Inotify& operator=(Inotify const&);

	public:
	Inotify();
	~Inotify();

	int fd()const;
};

class Watch{
	int fd,wd;

	Watch(Watch const&);
	Watch& operator=(Watch const&);

	public:
	explicit Watch(int fd1);
	~Watch();
};

class Watch_file{
	Inotify a;
	Watch b;

	Watch_file(Watch_file const&);
	Watch_file& operator=(Watch_file const&);

	public:
	Watch_file();

	//non-blocking
	bool change()const;
};

#endif
