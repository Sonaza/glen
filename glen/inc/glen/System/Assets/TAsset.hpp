#ifndef GLEN_TASSET_HPP
#define GLEN_TASSET_HPP

#include <string>
#include <cassert>

namespace glen
{

	template <class TYPE>
	class TAsset
	{
	public:
		TAsset(const std::string &path) :
		  m_asset(NULL),
			  m_loaded(false),
			  m_boundToScene(false),
			  m_filename(path) {}

		  ~TAsset() { if(m_loaded) unloadAsset(); }

		  virtual bool loadAsset() =0;
		  void unloadAsset();

		  inline TYPE* getAsset() const { return m_asset; }

		  inline void setSceneBound(const bool v) { m_boundToScene = v; }
		  inline bool isSceneBound() const { return m_boundToScene; }

	protected:

		TYPE*	m_asset;

		// Tells if asset is loaded and ready to use
		bool	m_loaded;

		std::string		m_filename;

		// States whether an asset is only needed for one scene
		// and can be freed once scene is changed
		bool	m_boundToScene;

	};

	////////////////////////////////////////////////////
	template <class TYPE>
	void TAsset<TYPE>::unloadAsset()
	{
		assert(m_asset != NULL && "Asset must not be null");

		delete m_asset;
		m_asset = NULL;

		m_loaded = false;
	}

}

#endif GLEN_TASSET_HPP
