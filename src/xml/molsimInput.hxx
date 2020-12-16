// Copyright (c) 2005-2014 Code Synthesis Tools CC
//
// This program was generated by CodeSynthesis XSD, an XML Schema to
// C++ data binding compiler.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
//
// In addition, as a special exception, Code Synthesis Tools CC gives
// permission to link this program with the Xerces-C++ library (or with
// modified versions of Xerces-C++ that use the same license as Xerces-C++),
// and distribute linked combinations including the two. You must obey
// the GNU General Public License version 2 in all respects for all of
// the code used other than Xerces-C++. If you modify this copy of the
// program, you may extend this exception to your version of the program,
// but you are not obligated to do so. If you do not wish to do so, delete
// this exception statement from your version.
//
// Furthermore, Code Synthesis Tools CC makes a special exception for
// the Free/Libre and Open Source Software (FLOSS) which is described
// in the accompanying FLOSSE file.
//

#ifndef MOLSIM_INPUT_HXX
#define MOLSIM_INPUT_HXX

#ifndef XSD_CXX11
#define XSD_CXX11
#endif

#ifndef XSD_USE_CHAR
#define XSD_USE_CHAR
#endif

#ifndef XSD_CXX_TREE_USE_CHAR
#define XSD_CXX_TREE_USE_CHAR
#endif

// Begin prologue.
//
//
// End prologue.

#include <xsd/cxx/config.hxx>

#if (XSD_INT_VERSION != 4000000L)
#error XSD runtime version mismatch
#endif

#include <xsd/cxx/pre.hxx>

#include <xsd/cxx/xml/char-utf8.hxx>

#include <xsd/cxx/tree/exceptions.hxx>
#include <xsd/cxx/tree/elements.hxx>
#include <xsd/cxx/tree/types.hxx>

#include <xsd/cxx/xml/error-handler.hxx>

#include <xsd/cxx/xml/dom/auto-ptr.hxx>

#include <xsd/cxx/tree/parsing.hxx>
#include <xsd/cxx/tree/parsing/byte.hxx>
#include <xsd/cxx/tree/parsing/unsigned-byte.hxx>
#include <xsd/cxx/tree/parsing/short.hxx>
#include <xsd/cxx/tree/parsing/unsigned-short.hxx>
#include <xsd/cxx/tree/parsing/int.hxx>
#include <xsd/cxx/tree/parsing/unsigned-int.hxx>
#include <xsd/cxx/tree/parsing/long.hxx>
#include <xsd/cxx/tree/parsing/unsigned-long.hxx>
#include <xsd/cxx/tree/parsing/boolean.hxx>
#include <xsd/cxx/tree/parsing/float.hxx>
#include <xsd/cxx/tree/parsing/double.hxx>
#include <xsd/cxx/tree/parsing/decimal.hxx>

namespace xml_schema
{
  // anyType and anySimpleType.
  //
  typedef ::xsd::cxx::tree::type type;
  typedef ::xsd::cxx::tree::simple_type< char, type > simple_type;
  typedef ::xsd::cxx::tree::type container;

  // 8-bit
  //
  typedef signed char byte;
  typedef unsigned char unsigned_byte;

  // 16-bit
  //
  typedef short short_;
  typedef unsigned short unsigned_short;

  // 32-bit
  //
  typedef int int_;
  typedef unsigned int unsigned_int;

  // 64-bit
  //
  typedef long long long_;
  typedef unsigned long long unsigned_long;

  // Supposed to be arbitrary-length integral types.
  //
  typedef long long integer;
  typedef long long non_positive_integer;
  typedef unsigned long long non_negative_integer;
  typedef unsigned long long positive_integer;
  typedef long long negative_integer;

  // Boolean.
  //
  typedef bool boolean;

  // Floating-point types.
  //
  typedef float float_;
  typedef double double_;
  typedef double decimal;

  // String types.
  //
  typedef ::xsd::cxx::tree::string< char, simple_type > string;
  typedef ::xsd::cxx::tree::normalized_string< char, string > normalized_string;
  typedef ::xsd::cxx::tree::token< char, normalized_string > token;
  typedef ::xsd::cxx::tree::name< char, token > name;
  typedef ::xsd::cxx::tree::nmtoken< char, token > nmtoken;
  typedef ::xsd::cxx::tree::nmtokens< char, simple_type, nmtoken > nmtokens;
  typedef ::xsd::cxx::tree::ncname< char, name > ncname;
  typedef ::xsd::cxx::tree::language< char, token > language;

  // ID/IDREF.
  //
  typedef ::xsd::cxx::tree::id< char, ncname > id;
  typedef ::xsd::cxx::tree::idref< char, ncname, type > idref;
  typedef ::xsd::cxx::tree::idrefs< char, simple_type, idref > idrefs;

  // URI.
  //
  typedef ::xsd::cxx::tree::uri< char, simple_type > uri;

  // Qualified name.
  //
  typedef ::xsd::cxx::tree::qname< char, simple_type, uri, ncname > qname;

  // Binary.
  //
  typedef ::xsd::cxx::tree::buffer< char > buffer;
  typedef ::xsd::cxx::tree::base64_binary< char, simple_type > base64_binary;
  typedef ::xsd::cxx::tree::hex_binary< char, simple_type > hex_binary;

  // Date/time.
  //
  typedef ::xsd::cxx::tree::time_zone time_zone;
  typedef ::xsd::cxx::tree::date< char, simple_type > date;
  typedef ::xsd::cxx::tree::date_time< char, simple_type > date_time;
  typedef ::xsd::cxx::tree::duration< char, simple_type > duration;
  typedef ::xsd::cxx::tree::gday< char, simple_type > gday;
  typedef ::xsd::cxx::tree::gmonth< char, simple_type > gmonth;
  typedef ::xsd::cxx::tree::gmonth_day< char, simple_type > gmonth_day;
  typedef ::xsd::cxx::tree::gyear< char, simple_type > gyear;
  typedef ::xsd::cxx::tree::gyear_month< char, simple_type > gyear_month;
  typedef ::xsd::cxx::tree::time< char, simple_type > time;

  // Entity.
  //
  typedef ::xsd::cxx::tree::entity< char, ncname > entity;
  typedef ::xsd::cxx::tree::entities< char, simple_type, entity > entities;

  typedef ::xsd::cxx::tree::content_order content_order;
  // Flags and properties.
  //
  typedef ::xsd::cxx::tree::flags flags;
  typedef ::xsd::cxx::tree::properties< char > properties;

  // Parsing/serialization diagnostics.
  //
  typedef ::xsd::cxx::tree::severity severity;
  typedef ::xsd::cxx::tree::error< char > error;
  typedef ::xsd::cxx::tree::diagnostics< char > diagnostics;

  // Exceptions.
  //
  typedef ::xsd::cxx::tree::exception< char > exception;
  typedef ::xsd::cxx::tree::bounds< char > bounds;
  typedef ::xsd::cxx::tree::duplicate_id< char > duplicate_id;
  typedef ::xsd::cxx::tree::parsing< char > parsing;
  typedef ::xsd::cxx::tree::expected_element< char > expected_element;
  typedef ::xsd::cxx::tree::unexpected_element< char > unexpected_element;
  typedef ::xsd::cxx::tree::expected_attribute< char > expected_attribute;
  typedef ::xsd::cxx::tree::unexpected_enumerator< char > unexpected_enumerator;
  typedef ::xsd::cxx::tree::expected_text_content< char > expected_text_content;
  typedef ::xsd::cxx::tree::no_prefix_mapping< char > no_prefix_mapping;

  // Error handler callback interface.
  //
  typedef ::xsd::cxx::xml::error_handler< char > error_handler;

  // DOM interaction.
  //
  namespace dom
  {
    // Automatic pointer for DOMDocument.
    //
    using ::xsd::cxx::xml::dom::unique_ptr;

#ifndef XSD_CXX_TREE_TREE_NODE_KEY__XML_SCHEMA
#define XSD_CXX_TREE_TREE_NODE_KEY__XML_SCHEMA
    // DOM user data key for back pointers to tree nodes.
    //
    const XMLCh* const tree_node_key = ::xsd::cxx::tree::user_data_keys::node;
#endif
  }
}

// Forward declarations.
//
class double_vector;
class integer_vector;
class cuboid;
class cuboid_cluster;
class particle;
class particle_cluster;
class sphere;
class sphere_cluster;
class particle_data;
class boundary_type;
class domain_type;
class molsimInput;

#include <memory>    // ::std::unique_ptr
#include <limits>    // std::numeric_limits
#include <algorithm> // std::binary_search
#include <utility>   // std::move

#include <xsd/cxx/xml/char-utf8.hxx>

#include <xsd/cxx/tree/exceptions.hxx>
#include <xsd/cxx/tree/elements.hxx>
#include <xsd/cxx/tree/containers.hxx>
#include <xsd/cxx/tree/list.hxx>

#include <xsd/cxx/xml/dom/parsing-header.hxx>

class double_vector: public ::xml_schema::type
{
  public:
  // x
  //
  typedef ::xml_schema::double_ x_type;
  typedef ::xsd::cxx::tree::traits< x_type, char, ::xsd::cxx::tree::schema_type::double_ > x_traits;

  const x_type&
  x () const;

  x_type&
  x ();

  void
  x (const x_type& x);

  // y
  //
  typedef ::xml_schema::double_ y_type;
  typedef ::xsd::cxx::tree::traits< y_type, char, ::xsd::cxx::tree::schema_type::double_ > y_traits;

  const y_type&
  y () const;

  y_type&
  y ();

  void
  y (const y_type& x);

  // z
  //
  typedef ::xml_schema::double_ z_type;
  typedef ::xsd::cxx::tree::traits< z_type, char, ::xsd::cxx::tree::schema_type::double_ > z_traits;

  const z_type&
  z () const;

  z_type&
  z ();

  void
  z (const z_type& x);

  // Constructors.
  //
  double_vector (const x_type&,
                 const y_type&,
                 const z_type&);

  double_vector (const ::xercesc::DOMElement& e,
                 ::xml_schema::flags f = 0,
                 ::xml_schema::container* c = 0);

  double_vector (const double_vector& x,
                 ::xml_schema::flags f = 0,
                 ::xml_schema::container* c = 0);

  virtual double_vector*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  double_vector&
  operator= (const double_vector& x);

  virtual 
  ~double_vector ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< x_type > x_;
  ::xsd::cxx::tree::one< y_type > y_;
  ::xsd::cxx::tree::one< z_type > z_;
};

class integer_vector: public ::xml_schema::type
{
  public:
  // x
  //
  typedef ::xml_schema::int_ x_type;
  typedef ::xsd::cxx::tree::traits< x_type, char > x_traits;

  const x_type&
  x () const;

  x_type&
  x ();

  void
  x (const x_type& x);

  // y
  //
  typedef ::xml_schema::int_ y_type;
  typedef ::xsd::cxx::tree::traits< y_type, char > y_traits;

  const y_type&
  y () const;

  y_type&
  y ();

  void
  y (const y_type& x);

  // z
  //
  typedef ::xml_schema::int_ z_type;
  typedef ::xsd::cxx::tree::traits< z_type, char > z_traits;

  const z_type&
  z () const;

  z_type&
  z ();

  void
  z (const z_type& x);

  // Constructors.
  //
  integer_vector (const x_type&,
                  const y_type&,
                  const z_type&);

  integer_vector (const ::xercesc::DOMElement& e,
                  ::xml_schema::flags f = 0,
                  ::xml_schema::container* c = 0);

  integer_vector (const integer_vector& x,
                  ::xml_schema::flags f = 0,
                  ::xml_schema::container* c = 0);

  virtual integer_vector*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  integer_vector&
  operator= (const integer_vector& x);

  virtual 
  ~integer_vector ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< x_type > x_;
  ::xsd::cxx::tree::one< y_type > y_;
  ::xsd::cxx::tree::one< z_type > z_;
};

class cuboid: public ::xml_schema::type
{
  public:
  // position
  //
  typedef ::double_vector position_type;
  typedef ::xsd::cxx::tree::traits< position_type, char > position_traits;

  const position_type&
  position () const;

  position_type&
  position ();

  void
  position (const position_type& x);

  void
  position (::std::unique_ptr< position_type > p);

  // size
  //
  typedef ::integer_vector size_type;
  typedef ::xsd::cxx::tree::traits< size_type, char > size_traits;

  const size_type&
  size () const;

  size_type&
  size ();

  void
  size (const size_type& x);

  void
  size (::std::unique_ptr< size_type > p);

  // distance
  //
  typedef ::xml_schema::double_ distance_type;
  typedef ::xsd::cxx::tree::traits< distance_type, char, ::xsd::cxx::tree::schema_type::double_ > distance_traits;

  const distance_type&
  distance () const;

  distance_type&
  distance ();

  void
  distance (const distance_type& x);

  // mass
  //
  typedef ::xml_schema::double_ mass_type;
  typedef ::xsd::cxx::tree::traits< mass_type, char, ::xsd::cxx::tree::schema_type::double_ > mass_traits;

  const mass_type&
  mass () const;

  mass_type&
  mass ();

  void
  mass (const mass_type& x);

  // velocity
  //
  typedef ::double_vector velocity_type;
  typedef ::xsd::cxx::tree::traits< velocity_type, char > velocity_traits;

  const velocity_type&
  velocity () const;

  velocity_type&
  velocity ();

  void
  velocity (const velocity_type& x);

  void
  velocity (::std::unique_ptr< velocity_type > p);

  // meanv
  //
  typedef ::xml_schema::double_ meanv_type;
  typedef ::xsd::cxx::tree::traits< meanv_type, char, ::xsd::cxx::tree::schema_type::double_ > meanv_traits;

  const meanv_type&
  meanv () const;

  meanv_type&
  meanv ();

  void
  meanv (const meanv_type& x);

  // Constructors.
  //
  cuboid (const position_type&,
          const size_type&,
          const distance_type&,
          const mass_type&,
          const velocity_type&,
          const meanv_type&);

  cuboid (::std::unique_ptr< position_type >,
          ::std::unique_ptr< size_type >,
          const distance_type&,
          const mass_type&,
          ::std::unique_ptr< velocity_type >,
          const meanv_type&);

  cuboid (const ::xercesc::DOMElement& e,
          ::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0);

  cuboid (const cuboid& x,
          ::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0);

  virtual cuboid*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  cuboid&
  operator= (const cuboid& x);

  virtual 
  ~cuboid ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< position_type > position_;
  ::xsd::cxx::tree::one< size_type > size_;
  ::xsd::cxx::tree::one< distance_type > distance_;
  ::xsd::cxx::tree::one< mass_type > mass_;
  ::xsd::cxx::tree::one< velocity_type > velocity_;
  ::xsd::cxx::tree::one< meanv_type > meanv_;
};

class cuboid_cluster: public ::xml_schema::type
{
  public:
  // cuboid
  //
  typedef ::cuboid cuboid_type;
  typedef ::xsd::cxx::tree::sequence< cuboid_type > cuboid_sequence;
  typedef cuboid_sequence::iterator cuboid_iterator;
  typedef cuboid_sequence::const_iterator cuboid_const_iterator;
  typedef ::xsd::cxx::tree::traits< cuboid_type, char > cuboid_traits;

  const cuboid_sequence&
  cuboid () const;

  cuboid_sequence&
  cuboid ();

  void
  cuboid (const cuboid_sequence& s);

  // Constructors.
  //
  cuboid_cluster ();

  cuboid_cluster (const ::xercesc::DOMElement& e,
                  ::xml_schema::flags f = 0,
                  ::xml_schema::container* c = 0);

  cuboid_cluster (const cuboid_cluster& x,
                  ::xml_schema::flags f = 0,
                  ::xml_schema::container* c = 0);

  virtual cuboid_cluster*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  cuboid_cluster&
  operator= (const cuboid_cluster& x);

  virtual 
  ~cuboid_cluster ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  cuboid_sequence cuboid_;
};

class particle: public ::xml_schema::type
{
  public:
  // x
  //
  typedef ::double_vector x_type;
  typedef ::xsd::cxx::tree::traits< x_type, char > x_traits;

  const x_type&
  x () const;

  x_type&
  x ();

  void
  x (const x_type& x);

  void
  x (::std::unique_ptr< x_type > p);

  // v
  //
  typedef ::double_vector v_type;
  typedef ::xsd::cxx::tree::traits< v_type, char > v_traits;

  const v_type&
  v () const;

  v_type&
  v ();

  void
  v (const v_type& x);

  void
  v (::std::unique_ptr< v_type > p);

  // m
  //
  typedef ::xml_schema::double_ m_type;
  typedef ::xsd::cxx::tree::traits< m_type, char, ::xsd::cxx::tree::schema_type::double_ > m_traits;

  const m_type&
  m () const;

  m_type&
  m ();

  void
  m (const m_type& x);

  // Constructors.
  //
  particle (const x_type&,
            const v_type&,
            const m_type&);

  particle (::std::unique_ptr< x_type >,
            ::std::unique_ptr< v_type >,
            const m_type&);

  particle (const ::xercesc::DOMElement& e,
            ::xml_schema::flags f = 0,
            ::xml_schema::container* c = 0);

  particle (const particle& x,
            ::xml_schema::flags f = 0,
            ::xml_schema::container* c = 0);

  virtual particle*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  particle&
  operator= (const particle& x);

  virtual 
  ~particle ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< x_type > x_;
  ::xsd::cxx::tree::one< v_type > v_;
  ::xsd::cxx::tree::one< m_type > m_;
};

class particle_cluster: public ::xml_schema::type
{
  public:
  // particle
  //
  typedef ::particle particle_type;
  typedef ::xsd::cxx::tree::sequence< particle_type > particle_sequence;
  typedef particle_sequence::iterator particle_iterator;
  typedef particle_sequence::const_iterator particle_const_iterator;
  typedef ::xsd::cxx::tree::traits< particle_type, char > particle_traits;

  const particle_sequence&
  particle () const;

  particle_sequence&
  particle ();

  void
  particle (const particle_sequence& s);

  // Constructors.
  //
  particle_cluster ();

  particle_cluster (const ::xercesc::DOMElement& e,
                    ::xml_schema::flags f = 0,
                    ::xml_schema::container* c = 0);

  particle_cluster (const particle_cluster& x,
                    ::xml_schema::flags f = 0,
                    ::xml_schema::container* c = 0);

  virtual particle_cluster*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  particle_cluster&
  operator= (const particle_cluster& x);

  virtual 
  ~particle_cluster ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  particle_sequence particle_;
};

class sphere: public ::xml_schema::type
{
  public:
  // center
  //
  typedef ::double_vector center_type;
  typedef ::xsd::cxx::tree::traits< center_type, char > center_traits;

  const center_type&
  center () const;

  center_type&
  center ();

  void
  center (const center_type& x);

  void
  center (::std::unique_ptr< center_type > p);

  // d
  //
  typedef ::xml_schema::double_ d_type;
  typedef ::xsd::cxx::tree::traits< d_type, char, ::xsd::cxx::tree::schema_type::double_ > d_traits;

  const d_type&
  d () const;

  d_type&
  d ();

  void
  d (const d_type& x);

  // v
  //
  typedef ::double_vector v_type;
  typedef ::xsd::cxx::tree::traits< v_type, char > v_traits;

  const v_type&
  v () const;

  v_type&
  v ();

  void
  v (const v_type& x);

  void
  v (::std::unique_ptr< v_type > p);

  // m
  //
  typedef ::xml_schema::double_ m_type;
  typedef ::xsd::cxx::tree::traits< m_type, char, ::xsd::cxx::tree::schema_type::double_ > m_traits;

  const m_type&
  m () const;

  m_type&
  m ();

  void
  m (const m_type& x);

  // r
  //
  typedef ::integer_vector r_type;
  typedef ::xsd::cxx::tree::traits< r_type, char > r_traits;

  const r_type&
  r () const;

  r_type&
  r ();

  void
  r (const r_type& x);

  void
  r (::std::unique_ptr< r_type > p);

  // Constructors.
  //
  sphere (const center_type&,
          const d_type&,
          const v_type&,
          const m_type&,
          const r_type&);

  sphere (::std::unique_ptr< center_type >,
          const d_type&,
          ::std::unique_ptr< v_type >,
          const m_type&,
          ::std::unique_ptr< r_type >);

  sphere (const ::xercesc::DOMElement& e,
          ::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0);

  sphere (const sphere& x,
          ::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0);

  virtual sphere*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  sphere&
  operator= (const sphere& x);

  virtual 
  ~sphere ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< center_type > center_;
  ::xsd::cxx::tree::one< d_type > d_;
  ::xsd::cxx::tree::one< v_type > v_;
  ::xsd::cxx::tree::one< m_type > m_;
  ::xsd::cxx::tree::one< r_type > r_;
};

class sphere_cluster: public ::xml_schema::type
{
  public:
  // sphere
  //
  typedef ::sphere sphere_type;
  typedef ::xsd::cxx::tree::sequence< sphere_type > sphere_sequence;
  typedef sphere_sequence::iterator sphere_iterator;
  typedef sphere_sequence::const_iterator sphere_const_iterator;
  typedef ::xsd::cxx::tree::traits< sphere_type, char > sphere_traits;

  const sphere_sequence&
  sphere () const;

  sphere_sequence&
  sphere ();

  void
  sphere (const sphere_sequence& s);

  // Constructors.
  //
  sphere_cluster ();

  sphere_cluster (const ::xercesc::DOMElement& e,
                  ::xml_schema::flags f = 0,
                  ::xml_schema::container* c = 0);

  sphere_cluster (const sphere_cluster& x,
                  ::xml_schema::flags f = 0,
                  ::xml_schema::container* c = 0);

  virtual sphere_cluster*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  sphere_cluster&
  operator= (const sphere_cluster& x);

  virtual 
  ~sphere_cluster ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  sphere_sequence sphere_;
};

class particle_data: public ::xml_schema::type
{
  public:
  // is3D
  //
  typedef ::xml_schema::boolean is3D_type;
  typedef ::xsd::cxx::tree::traits< is3D_type, char > is3D_traits;

  const is3D_type&
  is3D () const;

  is3D_type&
  is3D ();

  void
  is3D (const is3D_type& x);

  // cuboids
  //
  typedef ::cuboid_cluster cuboids_type;
  typedef ::xsd::cxx::tree::traits< cuboids_type, char > cuboids_traits;

  const cuboids_type&
  cuboids () const;

  cuboids_type&
  cuboids ();

  void
  cuboids (const cuboids_type& x);

  void
  cuboids (::std::unique_ptr< cuboids_type > p);

  // particles
  //
  typedef ::particle_cluster particles_type;
  typedef ::xsd::cxx::tree::traits< particles_type, char > particles_traits;

  const particles_type&
  particles () const;

  particles_type&
  particles ();

  void
  particles (const particles_type& x);

  void
  particles (::std::unique_ptr< particles_type > p);

  // spheres
  //
  typedef ::sphere_cluster spheres_type;
  typedef ::xsd::cxx::tree::traits< spheres_type, char > spheres_traits;

  const spheres_type&
  spheres () const;

  spheres_type&
  spheres ();

  void
  spheres (const spheres_type& x);

  void
  spheres (::std::unique_ptr< spheres_type > p);

  // Constructors.
  //
  particle_data (const is3D_type&,
                 const cuboids_type&,
                 const particles_type&,
                 const spheres_type&);

  particle_data (const is3D_type&,
                 ::std::unique_ptr< cuboids_type >,
                 ::std::unique_ptr< particles_type >,
                 ::std::unique_ptr< spheres_type >);

  particle_data (const ::xercesc::DOMElement& e,
                 ::xml_schema::flags f = 0,
                 ::xml_schema::container* c = 0);

  particle_data (const particle_data& x,
                 ::xml_schema::flags f = 0,
                 ::xml_schema::container* c = 0);

  virtual particle_data*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  particle_data&
  operator= (const particle_data& x);

  virtual 
  ~particle_data ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< is3D_type > is3D_;
  ::xsd::cxx::tree::one< cuboids_type > cuboids_;
  ::xsd::cxx::tree::one< particles_type > particles_;
  ::xsd::cxx::tree::one< spheres_type > spheres_;
};

class boundary_type: public ::xml_schema::type
{
  public:
  // front
  //
  typedef ::xml_schema::boolean front_type;
  typedef ::xsd::cxx::tree::traits< front_type, char > front_traits;

  const front_type&
  front () const;

  front_type&
  front ();

  void
  front (const front_type& x);

  // back
  //
  typedef ::xml_schema::boolean back_type;
  typedef ::xsd::cxx::tree::traits< back_type, char > back_traits;

  const back_type&
  back () const;

  back_type&
  back ();

  void
  back (const back_type& x);

  // top
  //
  typedef ::xml_schema::boolean top_type;
  typedef ::xsd::cxx::tree::traits< top_type, char > top_traits;

  const top_type&
  top () const;

  top_type&
  top ();

  void
  top (const top_type& x);

  // bottom
  //
  typedef ::xml_schema::boolean bottom_type;
  typedef ::xsd::cxx::tree::traits< bottom_type, char > bottom_traits;

  const bottom_type&
  bottom () const;

  bottom_type&
  bottom ();

  void
  bottom (const bottom_type& x);

  // left
  //
  typedef ::xml_schema::boolean left_type;
  typedef ::xsd::cxx::tree::traits< left_type, char > left_traits;

  const left_type&
  left () const;

  left_type&
  left ();

  void
  left (const left_type& x);

  // right
  //
  typedef ::xml_schema::boolean right_type;
  typedef ::xsd::cxx::tree::traits< right_type, char > right_traits;

  const right_type&
  right () const;

  right_type&
  right ();

  void
  right (const right_type& x);

  // Constructors.
  //
  boundary_type (const front_type&,
                 const back_type&,
                 const top_type&,
                 const bottom_type&,
                 const left_type&,
                 const right_type&);

  boundary_type (const ::xercesc::DOMElement& e,
                 ::xml_schema::flags f = 0,
                 ::xml_schema::container* c = 0);

  boundary_type (const boundary_type& x,
                 ::xml_schema::flags f = 0,
                 ::xml_schema::container* c = 0);

  virtual boundary_type*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  boundary_type&
  operator= (const boundary_type& x);

  virtual 
  ~boundary_type ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< front_type > front_;
  ::xsd::cxx::tree::one< back_type > back_;
  ::xsd::cxx::tree::one< top_type > top_;
  ::xsd::cxx::tree::one< bottom_type > bottom_;
  ::xsd::cxx::tree::one< left_type > left_;
  ::xsd::cxx::tree::one< right_type > right_;
};

class domain_type: public ::xml_schema::type
{
  public:
  // domain_size
  //
  typedef ::double_vector domain_size_type;
  typedef ::xsd::cxx::tree::traits< domain_size_type, char > domain_size_traits;

  const domain_size_type&
  domain_size () const;

  domain_size_type&
  domain_size ();

  void
  domain_size (const domain_size_type& x);

  void
  domain_size (::std::unique_ptr< domain_size_type > p);

  // cutoff_radius
  //
  typedef ::xml_schema::double_ cutoff_radius_type;
  typedef ::xsd::cxx::tree::traits< cutoff_radius_type, char, ::xsd::cxx::tree::schema_type::double_ > cutoff_radius_traits;

  const cutoff_radius_type&
  cutoff_radius () const;

  cutoff_radius_type&
  cutoff_radius ();

  void
  cutoff_radius (const cutoff_radius_type& x);

  // boundary
  //
  typedef ::boundary_type boundary_type;
  typedef ::xsd::cxx::tree::traits< boundary_type, char > boundary_traits;

  const boundary_type&
  boundary () const;

  boundary_type&
  boundary ();

  void
  boundary (const boundary_type& x);

  void
  boundary (::std::unique_ptr< boundary_type > p);

  // Constructors.
  //
  domain_type (const domain_size_type&,
               const cutoff_radius_type&,
               const boundary_type&);

  domain_type (::std::unique_ptr< domain_size_type >,
               const cutoff_radius_type&,
               ::std::unique_ptr< boundary_type >);

  domain_type (const ::xercesc::DOMElement& e,
               ::xml_schema::flags f = 0,
               ::xml_schema::container* c = 0);

  domain_type (const domain_type& x,
               ::xml_schema::flags f = 0,
               ::xml_schema::container* c = 0);

  virtual domain_type*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  domain_type&
  operator= (const domain_type& x);

  virtual 
  ~domain_type ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  ::xsd::cxx::tree::one< domain_size_type > domain_size_;
  ::xsd::cxx::tree::one< cutoff_radius_type > cutoff_radius_;
  ::xsd::cxx::tree::one< boundary_type > boundary_;
};

class molsimInput: public ::xml_schema::type
{
  public:
  // name_output
  //
  typedef ::xml_schema::string name_output_type;
  typedef ::xsd::cxx::tree::optional< name_output_type > name_output_optional;
  typedef ::xsd::cxx::tree::traits< name_output_type, char > name_output_traits;

  const name_output_optional&
  name_output () const;

  name_output_optional&
  name_output ();

  void
  name_output (const name_output_type& x);

  void
  name_output (const name_output_optional& x);

  void
  name_output (::std::unique_ptr< name_output_type > p);

  // frequency_output
  //
  typedef ::xml_schema::int_ frequency_output_type;
  typedef ::xsd::cxx::tree::optional< frequency_output_type > frequency_output_optional;
  typedef ::xsd::cxx::tree::traits< frequency_output_type, char > frequency_output_traits;

  const frequency_output_optional&
  frequency_output () const;

  frequency_output_optional&
  frequency_output ();

  void
  frequency_output (const frequency_output_type& x);

  void
  frequency_output (const frequency_output_optional& x);

  // delta_t
  //
  typedef ::xml_schema::double_ delta_t_type;
  typedef ::xsd::cxx::tree::traits< delta_t_type, char, ::xsd::cxx::tree::schema_type::double_ > delta_t_traits;

  const delta_t_type&
  delta_t () const;

  delta_t_type&
  delta_t ();

  void
  delta_t (const delta_t_type& x);

  // t_end
  //
  typedef ::xml_schema::double_ t_end_type;
  typedef ::xsd::cxx::tree::traits< t_end_type, char, ::xsd::cxx::tree::schema_type::double_ > t_end_traits;

  const t_end_type&
  t_end () const;

  t_end_type&
  t_end ();

  void
  t_end (const t_end_type& x);

  // linked_cell
  //
  typedef ::xml_schema::boolean linked_cell_type;
  typedef ::xsd::cxx::tree::traits< linked_cell_type, char > linked_cell_traits;

  const linked_cell_type&
  linked_cell () const;

  linked_cell_type&
  linked_cell ();

  void
  linked_cell (const linked_cell_type& x);

  // domain
  //
  typedef ::domain_type domain_type;
  typedef ::xsd::cxx::tree::traits< domain_type, char > domain_traits;

  const domain_type&
  domain () const;

  domain_type&
  domain ();

  void
  domain (const domain_type& x);

  void
  domain (::std::unique_ptr< domain_type > p);

  // particle_data
  //
  typedef ::particle_data particle_data_type;
  typedef ::xsd::cxx::tree::traits< particle_data_type, char > particle_data_traits;

  const particle_data_type&
  particle_data () const;

  particle_data_type&
  particle_data ();

  void
  particle_data (const particle_data_type& x);

  void
  particle_data (::std::unique_ptr< particle_data_type > p);

  // Constructors.
  //
  molsimInput (const delta_t_type&,
               const t_end_type&,
               const linked_cell_type&,
               const domain_type&,
               const particle_data_type&);

  molsimInput (const delta_t_type&,
               const t_end_type&,
               const linked_cell_type&,
               ::std::unique_ptr< domain_type >,
               ::std::unique_ptr< particle_data_type >);

  molsimInput (const ::xercesc::DOMElement& e,
               ::xml_schema::flags f = 0,
               ::xml_schema::container* c = 0);

  molsimInput (const molsimInput& x,
               ::xml_schema::flags f = 0,
               ::xml_schema::container* c = 0);

  virtual molsimInput*
  _clone (::xml_schema::flags f = 0,
          ::xml_schema::container* c = 0) const;

  molsimInput&
  operator= (const molsimInput& x);

  virtual 
  ~molsimInput ();

  // Implementation.
  //
  protected:
  void
  parse (::xsd::cxx::xml::dom::parser< char >&,
         ::xml_schema::flags);

  protected:
  name_output_optional name_output_;
  frequency_output_optional frequency_output_;
  ::xsd::cxx::tree::one< delta_t_type > delta_t_;
  ::xsd::cxx::tree::one< t_end_type > t_end_;
  ::xsd::cxx::tree::one< linked_cell_type > linked_cell_;
  ::xsd::cxx::tree::one< domain_type > domain_;
  ::xsd::cxx::tree::one< particle_data_type > particle_data_;
};

#include <iosfwd>

#include <xercesc/sax/InputSource.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMErrorHandler.hpp>

// Parse a URI or a local file.
//

::std::unique_ptr< ::molsimInput >
input (const ::std::string& uri,
       ::xml_schema::flags f = 0,
       const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::unique_ptr< ::molsimInput >
input (const ::std::string& uri,
       ::xml_schema::error_handler& eh,
       ::xml_schema::flags f = 0,
       const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::unique_ptr< ::molsimInput >
input (const ::std::string& uri,
       ::xercesc::DOMErrorHandler& eh,
       ::xml_schema::flags f = 0,
       const ::xml_schema::properties& p = ::xml_schema::properties ());

// Parse std::istream.
//

::std::unique_ptr< ::molsimInput >
input (::std::istream& is,
       ::xml_schema::flags f = 0,
       const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::unique_ptr< ::molsimInput >
input (::std::istream& is,
       ::xml_schema::error_handler& eh,
       ::xml_schema::flags f = 0,
       const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::unique_ptr< ::molsimInput >
input (::std::istream& is,
       ::xercesc::DOMErrorHandler& eh,
       ::xml_schema::flags f = 0,
       const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::unique_ptr< ::molsimInput >
input (::std::istream& is,
       const ::std::string& id,
       ::xml_schema::flags f = 0,
       const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::unique_ptr< ::molsimInput >
input (::std::istream& is,
       const ::std::string& id,
       ::xml_schema::error_handler& eh,
       ::xml_schema::flags f = 0,
       const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::unique_ptr< ::molsimInput >
input (::std::istream& is,
       const ::std::string& id,
       ::xercesc::DOMErrorHandler& eh,
       ::xml_schema::flags f = 0,
       const ::xml_schema::properties& p = ::xml_schema::properties ());

// Parse xercesc::InputSource.
//

::std::unique_ptr< ::molsimInput >
input (::xercesc::InputSource& is,
       ::xml_schema::flags f = 0,
       const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::unique_ptr< ::molsimInput >
input (::xercesc::InputSource& is,
       ::xml_schema::error_handler& eh,
       ::xml_schema::flags f = 0,
       const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::unique_ptr< ::molsimInput >
input (::xercesc::InputSource& is,
       ::xercesc::DOMErrorHandler& eh,
       ::xml_schema::flags f = 0,
       const ::xml_schema::properties& p = ::xml_schema::properties ());

// Parse xercesc::DOMDocument.
//

::std::unique_ptr< ::molsimInput >
input (const ::xercesc::DOMDocument& d,
       ::xml_schema::flags f = 0,
       const ::xml_schema::properties& p = ::xml_schema::properties ());

::std::unique_ptr< ::molsimInput >
input (::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d,
       ::xml_schema::flags f = 0,
       const ::xml_schema::properties& p = ::xml_schema::properties ());

#include <xsd/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.

#endif // MOLSIM_INPUT_HXX
