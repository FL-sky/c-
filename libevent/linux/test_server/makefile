test_server:test_server.cpp
	g++ $^ -o $@ -levent
	./$@
## $^ 依赖项 ## $@ 目标项
## libevent* 去掉前缀lib和后缀 成-levent

clean:
	rm -rf test_server
	rm -rf *.o