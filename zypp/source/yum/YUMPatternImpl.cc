/*---------------------------------------------------------------------\
|                          ____ _   __ __ ___                          |
|                         |__  / \ / / . \ . \                         |
|                           / / \ V /|  _/  _/                         |
|                          / /__ | | | | | |                           |
|                         /_____||_| |_| |_|                           |
|                                                                      |
\---------------------------------------------------------------------*/
/** \file zypp/source/yum/YUMPatternImpl.cc
 *
*/

#include "zypp/source/yum/YUMPatternImpl.h"
#include "zypp/CapFactory.h"

using namespace std;
using namespace zypp::detail;
using namespace zypp::parser::yum;

///////////////////////////////////////////////////////////////////
namespace zypp
{ /////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////
  namespace source
  { /////////////////////////////////////////////////////////////////
    namespace yum
    {
      ///////////////////////////////////////////////////////////////////
      //
      //        CLASS NAME : YUMPatternImpl
      //
      ///////////////////////////////////////////////////////////////////

      /** Default ctor
      */
      YUMPatternImpl::YUMPatternImpl(
	Source_Ref source_r,
	const zypp::parser::yum::YUMPatternData & parsed
      )
      : _user_visible(parsed.userVisible == "true")
      , _summary(parsed.name)
      , _description(parsed.description)
      , _default(parsed.default_ == "true")
      , _category(parsed.category)
      , _icon(parsed.icon)
      , _script(parsed.script)
      , _source(source_r)
      {

// to name        std::string patternId;
// as _summary        std::list<multilang> name;
// _description
      }
      /** Is to be visible for user? */
      bool YUMPatternImpl::userVisible() const {
	return _user_visible;
      }

      TranslatedText YUMPatternImpl::summary() const
      { return _summary; }

      TranslatedText YUMPatternImpl::description() const
      { return _description; }

      Text YUMPatternImpl::insnotify() const
      { return ResObjectImplIf::insnotify(); }

      Text YUMPatternImpl::delnotify() const
      { return ResObjectImplIf::delnotify(); }

      bool YUMPatternImpl::providesSources() const
      { return ResObjectImplIf::providesSources(); }

      Label YUMPatternImpl::instSrcLabel() const
      { return ResObjectImplIf::instSrcLabel(); }

      Vendor YUMPatternImpl::instSrcVendor() const
      { return ResObjectImplIf::instSrcVendor(); }

      ByteCount YUMPatternImpl::size() const
      { return ResObjectImplIf::size(); }

      Source_Ref YUMPatternImpl::source() const
      { return _source; }

      /** */
      bool YUMPatternImpl::isDefault() const
      { return _default; }
      /** */
      std::string YUMPatternImpl::category() const
      { return _category; }
      /** */
      Pathname YUMPatternImpl::icon() const
      { return _icon; }
      /** */
      Pathname YUMPatternImpl::script() const
      { return _script; }


    } // namespace yum
    /////////////////////////////////////////////////////////////////
  } // namespace source
  ///////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////
} // namespace zypp
///////////////////////////////////////////////////////////////////
