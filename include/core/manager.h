#pragma once

#include <vector>
#include <list>
#include <stdint.h>

#include "core/component.h"

namespace jormungandr
{
	template<class T>
	class Manager
	{
	public:
		std::vector<T> _datas;
		std::list<uint32_t> _freeID;
		uint32_t	_maxID;

		void init();
		uint32_t createData();

	protected:
		virtual void onInit() = 0;
		virtual void onCreate(uint32_t p_ID) = 0;
	};

	//================================================

	template<class T>
	void Manager<T>::init()
	{
		_datas.reserve(1024);
		_freeID.clear();
		_maxID = 0;

		onInit();
	}

	//================================================

	template<class T>
	uint32_t Manager<T>::createData()
	{
		uint32_t id = 0;

		if(_freeID.size() != 0)
		{
			id = _freeID.back();
			_freeID.pop_back();
		}
		else
		{
			if(_maxID == _datas.capacity())
			{
				uint32_t newSize = _datas.size() + 512;
				_datas.reserve(newSize);
			}

			id = _maxID;
			++_maxID;

			_datas.resize(_datas.size() + 1);
		}

		jormungandr::manager::init(_datas.at(id), id);

		onCreate(id);

		return id;
	}
}