// 4.vector实现源码
#include <iostream>
#include <algorithm>
#include <assert.h>
#ifndef _CVECTOR_H_
#define _CVECTOR_H_
namespace cth
{
	class NoCopy
	{
	public:
		inline NoCopy() {}
		NoCopy(const NoCopy &);
		NoCopy &operator=(const NoCopy &);
	};
	template <typename T>
	class viterator : public std::iterator<std::forward_iterator_tag, T>
	{
	public:
		viterator()
		{
			t = NULL;
		}
		viterator(T *t_)
		{
			t = t_;
		}
		viterator(const viterator &other)
		{
			t = other.t;
		}
		viterator &operator=(const viterator &other)
		{
			t = other.t;
			return *this;
		}
		viterator &operator++()
		{
			t++;
			return *this;
		}
		viterator operator++(int)
		{
			viterator iter = *this;
			t++;
			return iter;
		}
		viterator operator+(int count)
		{
			viterator iter = *this;
			iter.t += count;
			return iter;
		}
		viterator &operator--()
		{

			t--;
			return *this;
		}
		viterator operator--(int)
		{
			viterator iter = *this;
			t--;
			return iter;
		}
		viterator operator-(int count)
		{
			viterator iter = *this;
			iter.t -= count;
			return iter;
		}
		int operator-(const viterator &other)
		{
			return t - other.t;
		}
		int operator-(const viterator &other) const
		{
			return t - other.t;
		}
		T &operator*()
		{
			return *t;
		}
		const T &operator*() const
		{
			return *t;
		}
		T *operator->()
		{
			return t;
		}
		const T *operator->() const
		{
			return t;
		}
		inline bool operator!=(const viterator &other)
		{
			return t != other.t;
		}
		inline bool operator!=(const viterator &other) const
		{
			return t != other.t;
		}
		inline bool operator==(const viterator &other)
		{
			return t == other.t;
		}
		inline bool operator==(const viterator &other) const
		{
			return t == other.t;
		}
		inline bool operator<(const viterator &other)
		{
			return t < other.t;
		}
		inline bool operator<(const viterator &other) const
		{
			return t < other.t;
		}
		inline bool operator<=(const viterator &other)
		{
			return t <= other.t;
		}
		inline bool operator<=(const viterator &other) const
		{
			return t <= other.t;
		}
		inline bool operator>(const viterator &other)
		{
			return t > other.t;
		}
		inline bool operator>(const viterator &other) const
		{
			return t > other.t;
		}
		inline bool operator>=(const viterator &other)
		{
			return t >= other.t;
		}
		inline bool operator>=(const viterator &other) const
		{
			return t >= other.t;
		}

	private:
		T *t;
	};
	template <typename T>
	class cvector : public NoCopy
	{
	public:
		typedef viterator<T> iterator;
		// viterator<T>就是对一个指针的包装，所以完全可以用T*代替viterator <T>
		typedef const viterator<T> const_iterator;
		// typedef T* iterator;
		// typedef const T* const_iterator;
		cvector()
		{
			initData(0);
		}
		cvector(int capa, const T &val = T())
		{
			initData(capa);
			newCapacity(capacity_);
			for (int i = 0; i < size_; i++)
				buf[i] = val;
		}
		cvector(const_iterator first, const_iterator last)
		{
			initData(last - first);
			newCapacity(capacity_);
			iterator iter = iterator(first);
			int index = 0;
			while (iter != last)
				buf[index++] = *iter++;
		}
		~cvector()
		{
			if (buf)
			{
				delete[] buf;
				buf = NULL;
			}
			size_ = capacity_ = 0;
		}
		void clear()
		{
			if (buf)
				erase(begin(), end());
		}
		void push_back(const T &t)
		{
			if (size_ == capacity_)
			{
				int capa = calculateCapacity();
				newCapacity(capa);
			}
			buf[size_++] = t;
		}
		void pop_back()
		{
			if (!empty())
				erase(end() - 1);
		}
		int insert(const_iterator iter, const T &t)
		{
			int index = iter - begin();
			if (index <= size_)
			{
				if (size_ == capacity_)
				{
					int capa = calculateCapacity();
					newCapacity(capa);
				}
				memmove(buf + index + 1, buf + index, (size_ - index) * sizeof(T));
				buf[index] = t;
				size_++;
			}
			return index;
		}
		iterator erase(const_iterator iter)
		{
			int index = iter - begin();
			if (index < size_ && size_ > 0)
			{
				memmove(buf + index, buf + index + 1, (size_ - index) * sizeof(T));
				buf[--size_] = T();
			}
			return iterator(iter);
		}
		iterator erase(const_iterator first, const_iterator last)
		{
			iterator first_ = iterator(first);
			iterator last_ = iterator(last);
			while (first_ <= last_--)
				erase(first_);
			return iterator(first_);
		}
		T &front()
		{
			assert(size_ > 0);
			return buf[0];
		}
		T &back()
		{
			assert(size_ > 0);
			return buf[size_ - 1];
		}
		T &at(int index)
		{
			assert(size_ > 0);
			return buf[index];
		}
		T &operator[](int index)
		{
			assert(size_ > 0 && index >= 0 && index < size_);
			return buf[index];
		}
		bool empty() const
		{
			return size_ == 0;
		}
		int size() const
		{
			return size_;
		}
		int capacity() const
		{
			return capacity_;
		}
		iterator begin()
		{
			return iterator(&buf[0]);
		}
		iterator end()
		{
			return iterator(&buf[size_]);
		}

	private:
		void newCapacity(int capa)
		{
			capacity_ = capa;
			T *newBuf = new T[capacity_];
			if (buf)
			{
				memcpy(newBuf, buf, size_ * sizeof(T));
				delete[] buf;
			}
			buf = newBuf;
		}
		inline int calculateCapacity()
		{
			return capacity_ * 3 / 2 + 1;
		}
		inline void initData(int capa)
		{
			buf = NULL;
			size_ = capacity_ = capa > 0 ? capa : 0;
		}
		int size_;
		int capacity_;
		T *buf;
	};
	//实例代码级运行结果
	struct Point
	{
		Point(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}
		int x, y;
	};
	bool operator<(const Point &p1, const Point &p2)
	{
		if (p1.x < p2.x)
		{
			return true;
		}
		else if (p1.x > p2.x)
		{
			return false;
		}
		return p1.y < p2.y;
	}
	void cvectorTest()
	{
		cvector<Point> vect;
		for (int i = 0; i < 10; i++)
		{
			Point p(i, i);
			vect.push_back(p);
		}
		cvector<Point>::iterator iter = vect.begin();
		while (iter != vect.end())
		{
			std::cout << "[" << iter->x << " " << iter->y << "], ";
			++iter;
		}
		iter = vect.begin() + 5;
		vect.insert(iter, Point(55, 55));
		iter = vect.end() - 3;
		vect.insert(iter, Point(77, 77));
		std::cout << std::endl
				  << std::endl
				  << "插入两个元素后：" << std::endl;
		iter = vect.begin();
		while (iter != vect.end())
		{
			std::cout << "[" << iter->x << " " << iter->y << "], ";
			++iter;
		}
		std::sort(vect.begin(), vect.end());
		std::cout << std::endl
				  << std::endl
				  << "排序后：" << std::endl;
		iter = vect.begin();
		while (iter != vect.end())
		{
			std::cout << "[" << iter->x << " " << iter->y << "], ";
			++iter;
		}
		vect.erase(vect.begin() + 10);
		vect.erase(vect.begin() + 10);
		std::cout << std::endl
				  << std::endl
				  << "删除之前新增的两个元素" << std::endl;
		iter = vect.begin();
		while (iter != vect.end())
		{
			std::cout << "[" << iter->x << " " << iter->y << "], ";
			++iter;
		}
		vect.clear();
		std::cout << std::endl
				  << std::endl
				  << "执行clear之后" << std::endl;
		std::cout << "size=" << vect.size() << ",capacity=" << vect.capacity();
		cvector<Point> vect1;
		for (int i = 10; i < 20; i++)
		{
			Point p(i, i);
			vect1.push_back(p);
		}
		std::cout << std::endl
				  << std::endl
				  << "从别的cvector复制数据:" << std::endl;
		cvector<Point> vect2(vect1.begin(), vect1.end());
		vect2.pop_back();
		vect2.pop_back();
		for (int i = 0; i < vect2.size(); i++)
		{
			std::cout << "[" << vect2[i].x << "," << vect2[i].y << "], ";
		}
		std::cout << std::endl;
	}
}
/// myadd
#endif
