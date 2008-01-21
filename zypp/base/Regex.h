/*---------------------------------------------------------------------\
|                          ____ _   __ __ ___                          |
|                         |__  / \ / / . \ . \                         |
|                           / / \ V /|  _/  _/                         |
|                          / /__ | | | | | |                           |
|                         /_____||_| |_| |_|                           |
|                                                                      |
\---------------------------------------------------------------------*/
/** \file zypp/base/Regex.h
 *
*/
#ifndef ZYPP_BASE_REGEX_H
#define ZYPP_BASE_REGEX_H

#include <iosfwd>
#include <string>

#include <regex.h>

#include "zypp/base/Exception.h"

///////////////////////////////////////////////////////////////////
namespace zypp
{ /////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////
  /** String related utilities and \ref ZYPP_STR_REGEX.
   \see \ref ZYPP_STR_REGEX
  */
  namespace str
  { /////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    /** \defgroup ZYPP_STR_REGEX Regular expressions
     *
     * Namespace zypp::str regular expressions \b using the
     * boost regex library
     * \url http://www.boost.org/libs/regex/doc/index.html.
     *
     * \li \c regex
     * \li \c regex_match
     * \li \c regex_search
     * \li \c regex_replace
     * \li \c match_results
     * \li \c cmatch
     * \li \c wcmatch
     * \li \c smatch
     * \li \c wsmatch
    */

    typedef Exception regex_error;

    class smatch;
    class regex;

    bool regex_match(const char * s, str::smatch& matches, const regex& regex);
    inline bool regex_match(const std::string& s, str::smatch& matches, const regex& regex)
    { return regex_match( s.c_str(), matches, regex ); }

    bool regex_match(const char * s, const regex& regex);
    inline bool regex_match(const std::string& s, const regex& regex)
    { return regex_match( s.c_str(), regex ); }

    class regex {
    public:

      enum RegFlags {
        optimize = 0,
        match_extra = 0,
        icase = REG_ICASE,
        nosubs = REG_NOSUB,
        match_extended = REG_EXTENDED,
        normal = 1<<16
      };

      regex();
      regex(const std::string& s,int flags = match_extended);
      ~regex() throw();

      void assign(const std::string& s,int flags = match_extended);

    private:
      friend class smatch;
      friend bool regex_match(const char * s, str::smatch& matches, const regex& regex);
      friend bool regex_match(const char * s,  const regex& regex);
      regex_t m_preg;
      bool m_valid;
    };

    class smatch {
    public:
      smatch();

      std::string operator[](unsigned i) const;

      unsigned size() const;

      std::string match_str;
      regmatch_t pmatch[12];
    };



    /////////////////////////////////////////////////////////////////
  } // namespace str
  ///////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////
} // namespace zypp
///////////////////////////////////////////////////////////////////
#endif // ZYPP_BASE_STRING_H
