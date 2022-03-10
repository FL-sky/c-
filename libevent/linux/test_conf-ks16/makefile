test_conf.out:test_conf.cpp
	g++ $^ -o $@ -levent
	./$@
## $^ 依赖项 ## $@ 目标项
## libevent* 去掉前缀lib和后缀 成-levent

clean:
	rm -rf *.out
	rm -rf *.o
