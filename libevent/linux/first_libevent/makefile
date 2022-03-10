firstlibevent:first_libevent.cpp
	g++ $^ -o $@ -levent
	./$@
## $^ 依赖项 ## $@ 目标项
## libevent* 去掉前缀lib和后缀 成-levent

clean:
	rm -rf firstlibevent
	rm -rf *.o