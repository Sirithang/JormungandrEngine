#pragma once

#include "core/manager.h"
#include "data/asset.h"
#include "data/data_types.h"

#include <map>
#include <string>

namespace jormungandr
{
	namespace data
	{
		struct AssetDatabase
		{
			std::map<std::string, Asset*> _assets;
		};



		//======================================================
		
		template<class T>
		struct AssetLoader
		{
			std::vector<T> _assets;
			std::list<uint32_t> _freeID;
			uint32_t _maxID;

			static AssetLoader<T> _instance;

			uint32_t create();
			T* create(const char* p_Path);

		protected:
			AssetLoader();
			bool _internalCreate(T& p_Created, const char* p_Path);
		};

		template<class T>
		AssetLoader<T> AssetLoader<T>::_instance;

		template<class T>
		AssetLoader<T>::AssetLoader()
		{
			_assets.reserve(512);
			_freeID.clear();
			_maxID = 0;
		}

		template<class T>
		uint32_t AssetLoader<T>::create()
		{
			uint32_t id;

			if(_freeID.size() > 0)
			{
				id = _freeID.back();
				_freeID.pop_back();
			}
			else
			{
				if(_maxID == _assets.capacity())
				{
					_assets.reserve(_assets.size() + 128);
				}

				id = _maxID;
				++_maxID;

				_assets.resize(_assets.size() + 1);
			}

			return id;
		}

		template<class T>
		T* AssetLoader<T>::create(const char* p_Path)
		{
			
			uint32_t id = create();
			
			return _internalCreate(_assets[id], p_Path) ? &_assets[id] : NULL; 
		}


		//********** Different Type implementation for the database 

		//---texture
		template<> 
		bool AssetLoader<Texture>::_internalCreate(Texture& p_Created, const char* p_File);


		//===========================================================

		extern AssetDatabase g_Database;

		namespace assetdatabase
		{

			//===========================================

			template<class T>
			T* load(const char* p_Path)
			{
				std::string path(p_Path);

				if(g_Database._assets.count(path) > 0)
				{
					return static_cast<T*>(g_Database._assets.at(path));
				}
				else
				{
					T* asset = AssetLoader<T>::_instance.create(p_Path);
					g_Database._assets[path] = asset;
					return asset;
				}

				return NULL;
			}
		}
	}
}