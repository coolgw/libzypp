/*---------------------------------------------------------------------\
|                          ____ _   __ __ ___                          |
|                         |__  / \ / / . \ . \                         |
|                           / / \ V /|  _/  _/                         |
|                          / /__ | | | | | |                           |
|                         /_____||_| |_| |_|                           |
|                                                                      |
\---------------------------------------------------------------------*/
/** \file zypp/data/ResolvableData.h
 *
*/
#ifndef ZYPP_DATA_RESOLVABLEDATA_H
#define ZYPP_DATA_RESOLVABLEDATA_H

#include <iosfwd>
#include <list>

#include "zypp/base/PtrTypes.h"
#include "zypp/base/ReferenceCounted.h"
#include "zypp/base/NonCopyable.h"

#include "zypp/data/RecordId.h"
#include "zypp/Pathname.h"
#include "zypp/Resolvable.h"
#include "zypp/NVR.h"
#include "zypp/Edition.h"
#include "zypp/ByteCount.h"
#include "zypp/Arch.h"
#include "zypp/CheckSum.h"
#include "zypp/Changelog.h"
#include "zypp/Url.h"
#include "zypp/Date.h"
#include "zypp/TranslatedText.h"
#include "zypp/OnMediaLocation.h"
#include "zypp/DiskUsage.h"

namespace zypp
{
namespace data
{
  typedef CapabilitySet                             DependencyList;
  typedef std::map<zypp::Dep, DependencyList>       Dependencies;

  typedef DefaultIntegral<unsigned,0u>              MediaNr;

  /** List of files contained in a package (info for UI) */
  typedef std::list<std::string>                    Filenames;

  ///////////////////////////////////////////////////////////////////

  DEFINE_PTR_TYPE(Resolvable);

  /** Mandatory resolvable data. */
  class Resolvable : public base::ReferenceCounted, private base::NonCopyable
  {
    public:
      Resolvable()
      {};

      /** Kind */
      ResKind     kind;
      /** Name */
      std::string name;
      /** Edition */
      Edition     edition;
      /** Architecture */
      Arch        arch;
      /** Dependencies */
      Dependencies deps;
  };

  ///////////////////////////////////////////////////////////////////

  DEFINE_PTR_TYPE(ResObject);

  /** Common resolvable data. */
  class ResObject : public Resolvable
  {
    public:
      ResObject()
      {}

      /** Raw data to determine \ref shareDataWith */
      std::string sharedDataTag;
      /** Share some data with another resolvable.*/
      RecordId shareDataWith;

      // Common attributes:
      /** Vendor */
      std::string vendor;
      /** Installed size (UI hint). */
      ByteCount installedSize;
      /** Bildtime. */
      Date buildTime;

      // Flags:
      /** 'rpm -i' mode. */
      DefaultIntegral<bool,false> installOnly;

      // Translated texts:
      /** One line summary. */
      TranslatedText summary;
      /** Multiline description. */
      TranslatedText description;
      /** License to confirm. */
      TranslatedText licenseToConfirm;
      /** UI notification text if selected to install. */
      TranslatedText insnotify;
      /** UI notification text if selected to delete. */
      TranslatedText delnotify;

      // Repository related:
      /** Repository providing this resolvable. */
      RecordId  repository;
    protected:
      /** Overload to realize std::ostream & operator\<\<. */
      virtual std::ostream & dumpOn( std::ostream & str ) const;
  };

  ///////////////////////////////////////////////////////////////////

  DEFINE_PTR_TYPE(Atom);

  /* Data Object for Atom resolvable. */
  class Atom : public ResObject
  {
    public:
      Atom()
      {};
  };

  ///////////////////////////////////////////////////////////////////

  DEFINE_PTR_TYPE(Script);

  /* Data Object for Script resolvable. */
  class Script : public ResObject
  {
    public:
      Script()
      {};

      /** Inlined doScript. */
      std::string doScript;
      /** Location of doScript on the repositories media. */
      OnMediaLocation doScriptLocation;

      /** Inlined undoScript. */
      std::string undoScript;
      /** Location of undoScript on the repositories media. */
      OnMediaLocation undoScriptLocation;
  };

  ///////////////////////////////////////////////////////////////////

  DEFINE_PTR_TYPE(Message);

  /* Data Object for Message resolvable. */
  class Message : public ResObject
  {
    public:
      Message()
      {};

      /** Inlined Text. */
      TranslatedText text;
  };

  ///////////////////////////////////////////////////////////////////

  DEFINE_PTR_TYPE(Patch);

  /* Data Object for Patch resolvable. */
  class Patch : public ResObject
  {
    public:
      Patch()
      {};

      /** Patch ID */
      std::string id;
      /** Patch time stamp */
      Date timestamp;
      /** Patch category (recommended, security,...) */
      std::string category;

      // Flags:
      /** Does the system need to reboot to finish the update process? */
      DefaultIntegral<bool,false> rebootNeeded;
      /** Does the patch affect the package manager itself? */
      DefaultIntegral<bool,false> affectsPkgManager;

      /** TODO Don't know what this is, but it's defined in patch.rnc */
      std::string updateScript;

      /**
       * The set of all atoms building the patch. These can be either
       * \ref PackageAtom, \ref Message or \ref Script.
       */
      std::set<ResObject_Ptr> atoms;
  };

  ///////////////////////////////////////////////////////////////////

  DEFINE_PTR_TYPE(Pattern);

  /* Data Object for Pattern resolvable. */
  class Pattern : public ResObject
  {
    public:
      Pattern()
      {}

      // Flags
      /** Should the pattern be installed by default? */
      DefaultIntegral<bool,false> isDefault;
      /** Visible or hidden at the UI. */
      DefaultIntegral<bool,false> userVisible;

      /** Category */
      TranslatedText category;

      /** Icon path relative to repository URL. */
      std::string icon;
      /** UI order string */
      std::string order;
      /** ? */
      std::string script;

      /** Included patterns. */
      DependencyList includes;
      /** Extended patterns. */
      DependencyList extends;
  };

  ///////////////////////////////////////////////////////////////////

  DEFINE_PTR_TYPE(Product);

  /* Data Object for Product resolvable. */
  class Product : public ResObject
  {
    public:
      Product()
      {};

      /** The product type (base, add-on) */
      std::string type;

      /** Abbreviation like \c SLES10 */
      TranslatedText shortName;
      /** More verbose Name like <tt>Suse Linux Enterprise Server 10</tt>*/
      TranslatedText longName;

      /** The product flags.
       * \todo What is it?
      */
      std::list<std::string> flags;

      /** Releasenotes url. */
      Url releasenotesUrl;
      /** Update repositories for the product. */
      std::list<Url> updateUrls;
      /** Additional software for the product.  */
      std::list<Url> extraUrls;
      /** Optional software for the product. */
      std::list<Url> optionalUrls;

      /** Vendor specific distribution id. */
      std::string distributionName;
      /** Vendor specific distribution version. */
      Edition distributionEdition;
  };

  ///////////////////////////////////////////////////////////////////

  DEFINE_PTR_TYPE(Packagebase);

  /**
   * Common Data Object for Package and Sourcepackage.
   *
   * We treat them as differend kind of Resolvable, but they have
   * almost identical data.
   */
  class Packagebase : public ResObject
  {
    public:
      enum PackageType { BIN, SRC, ATOM };
      virtual PackageType packageType() const = 0;

    public:
      /** Rpm group.*/
      std::string group;
      /** PackageDb keywors (tags). */
      std::set<std::string> keywords;

      /** Changelog. */
      Changelog changelog;
      /** Author list. */
      std::list<std::string> authors;


      /** Buildhost. */
      std::string buildhost;
      /** Distribution. */
      std::string distribution;
      /** Licensetype. Not the text you have to confirm. */
      std::string license;
      /** Packager. */
      std::string packager;
      /** Upstream home page URL.*/
      std::string url;

      /** operating system **/
      std::string operatingSystem;

      /** Pre install script. */
      std::string prein;
      /** Post install script. */
      std::string postin;
      /** Pre uninstall script. */
      std::string preun;
      /** Post uninstall script. */
      std::string postun;

      OnMediaLocation repositoryLocation;
      DiskUsage       diskusage;
  };

  DEFINE_PTR_TYPE(Package);
  /**
   * Data Object for Package resolvable
   */
  struct Package : public Packagebase
  {
    virtual PackageType packageType() const { return BIN; }

    /** NVR of the corresponding SrcPackage. */
    NVR srcPackageIdent;
  };

  DEFINE_PTR_TYPE(SrcPackage);
  /**
   * Data Object for SrcPackage resolvable
   */
  struct SrcPackage : public Packagebase
  {
    virtual PackageType packageType() const { return SRC; }
  };

  // --- ---------------------------------------------------------------------
  // --- the following are the data structures for storing YUM package atom
  // --- metadata (part of patch support). This is probably subject to change
  // --- in near future.
  // --- ---------------------------------------------------------------------

  DEFINE_PTR_TYPE(BaseVersion);
  /** Patch RPM baseversion */
  struct BaseVersion : public base::ReferenceCounted, private base::NonCopyable
  {
    Edition     edition;
  };

  /** Shared RPM attributes */
  struct RpmBase : public base::ReferenceCounted, private base::NonCopyable
  {
    // Base <patchrpm>/<deltarpm> element attributes

    std::string     name;     // target rpm name
    Edition         edition;  // target rpm edition
    Arch            arch;     // target rpm architecture
    OnMediaLocation location;
    Date            buildTime;
    Date            fileTime;
    ByteCount       archiveSize; // ??
    protected:
      /** Overload to realize std::ostream & operator\<\<. */
      virtual std::ostream & dumpOn( std::ostream & str ) const;
  };

  DEFINE_PTR_TYPE(PatchRpm);
  /** Patch RPM data object */
  struct PatchRpm : RpmBase
  {
    std::set<BaseVersion_Ptr> baseVersions;
  };

  DEFINE_PTR_TYPE(DeltaRpm);
  /** Delta RPM data object */
  struct DeltaRpm : RpmBase
  {
    struct DeltaBaseVersion : BaseVersion
    {
      Date        buildTime;
      CheckSum    checkSum;
      std::string sequenceInfo;
    };

    DeltaBaseVersion baseVersion;
  };

  DEFINE_PTR_TYPE(PackageAtom);
  /**
   * Data Object for YUM package atom.
   *
   * \see zypp/parser/yum/schema/patch.rng
   */
  struct PackageAtom : public Package
  {
    std::set<PatchRpm_Ptr> patchRpms;
    std::set<DeltaRpm_Ptr> deltaRpms;
    // TODO support mulitple licenses (licenseToConfirm)
  };

  // --- ----------END--YUM-package-atom-metadata-----------------------------

  ///////////////////////////////////////////////////////////////////

} // namespace data
} // namespace zypp
#endif // ZYPP_DATA_RESOLVABLEDATA_H
