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

#ifndef MOLSIM_INPUT_PSKEL_HXX
#define MOLSIM_INPUT_PSKEL_HXX

// Begin prologue.
//
//
// End prologue.

#include <xsd/cxx/config.hxx>

#if (XSD_INT_VERSION != 4000000L)
#error XSD runtime version mismatch
#endif

#include <xsd/cxx/pre.hxx>

// Forward declarations
//
class double_vector_pskel;
class integer_vector_pskel;
class cuboid_pskel;
class cuboid_cluster_pskel;
class particle_pskel;
class particle_cluster_pskel;
class input_particles_pskel;
class molsimInput_pskel;

#ifndef XSD_USE_CHAR
#define XSD_USE_CHAR
#endif

#ifndef XSD_CXX_PARSER_USE_CHAR
#define XSD_CXX_PARSER_USE_CHAR
#endif

#include <xsd/cxx/xml/char-utf8.hxx>
#include <xsd/cxx/xml/error-handler.hxx>
#include <xsd/cxx/parser/exceptions.hxx>
#include <xsd/cxx/parser/elements.hxx>
#include <xsd/cxx/parser/xml-schema.hxx>
#include <xsd/cxx/parser/non-validating/parser.hxx>
#include <xsd/cxx/parser/non-validating/xml-schema-pskel.hxx>
#include <xsd/cxx/parser/non-validating/xml-schema-pimpl.hxx>
#include <xsd/cxx/parser/xerces/elements.hxx>

//using namespace xml_schema;

namespace xml_schema
{
  // Built-in XML Schema types mapping.
  //
  typedef ::xsd::cxx::parser::string_sequence< char > string_sequence;
  typedef ::xsd::cxx::parser::qname< char > qname;
  typedef ::xsd::cxx::parser::buffer buffer;
  typedef ::xsd::cxx::parser::time_zone time_zone;
  typedef ::xsd::cxx::parser::gday gday;
  typedef ::xsd::cxx::parser::gmonth gmonth;
  typedef ::xsd::cxx::parser::gyear gyear;
  typedef ::xsd::cxx::parser::gmonth_day gmonth_day;
  typedef ::xsd::cxx::parser::gyear_month gyear_month;
  typedef ::xsd::cxx::parser::date date;
  typedef ::xsd::cxx::parser::time time;
  typedef ::xsd::cxx::parser::date_time date_time;
  typedef ::xsd::cxx::parser::duration duration;

  // Base parser skeletons.
  //
  typedef ::xsd::cxx::parser::parser_base< char > parser_base;
  typedef ::xsd::cxx::parser::non_validating::empty_content< char > empty_content;
  typedef ::xsd::cxx::parser::non_validating::simple_content< char > simple_content;
  typedef ::xsd::cxx::parser::non_validating::complex_content< char > complex_content;
  typedef ::xsd::cxx::parser::non_validating::list_base< char > list_base;

  // Parser skeletons and implementations for the XML Schema
  // built-in types.
  //
  typedef ::xsd::cxx::parser::non_validating::any_type_pskel< char > any_type_pskel;
  typedef ::xsd::cxx::parser::non_validating::any_type_pimpl< char > any_type_pimpl;

  typedef ::xsd::cxx::parser::non_validating::any_simple_type_pskel< char > any_simple_type_pskel;
  typedef ::xsd::cxx::parser::non_validating::any_simple_type_pimpl< char > any_simple_type_pimpl;

  typedef ::xsd::cxx::parser::non_validating::byte_pskel< char > byte_pskel;
  typedef ::xsd::cxx::parser::non_validating::byte_pimpl< char > byte_pimpl;

  typedef ::xsd::cxx::parser::non_validating::unsigned_byte_pskel< char > unsigned_byte_pskel;
  typedef ::xsd::cxx::parser::non_validating::unsigned_byte_pimpl< char > unsigned_byte_pimpl;

  typedef ::xsd::cxx::parser::non_validating::short_pskel< char > short_pskel;
  typedef ::xsd::cxx::parser::non_validating::short_pimpl< char > short_pimpl;

  typedef ::xsd::cxx::parser::non_validating::unsigned_short_pskel< char > unsigned_short_pskel;
  typedef ::xsd::cxx::parser::non_validating::unsigned_short_pimpl< char > unsigned_short_pimpl;

  typedef ::xsd::cxx::parser::non_validating::int_pskel< char > int_pskel;
  typedef ::xsd::cxx::parser::non_validating::int_pimpl< char > int_pimpl;

  typedef ::xsd::cxx::parser::non_validating::unsigned_int_pskel< char > unsigned_int_pskel;
  typedef ::xsd::cxx::parser::non_validating::unsigned_int_pimpl< char > unsigned_int_pimpl;

  typedef ::xsd::cxx::parser::non_validating::long_pskel< char > long_pskel;
  typedef ::xsd::cxx::parser::non_validating::long_pimpl< char > long_pimpl;

  typedef ::xsd::cxx::parser::non_validating::unsigned_long_pskel< char > unsigned_long_pskel;
  typedef ::xsd::cxx::parser::non_validating::unsigned_long_pimpl< char > unsigned_long_pimpl;

  typedef ::xsd::cxx::parser::non_validating::integer_pskel< char > integer_pskel;
  typedef ::xsd::cxx::parser::non_validating::integer_pimpl< char > integer_pimpl;

  typedef ::xsd::cxx::parser::non_validating::non_positive_integer_pskel< char > non_positive_integer_pskel;
  typedef ::xsd::cxx::parser::non_validating::non_positive_integer_pimpl< char > non_positive_integer_pimpl;

  typedef ::xsd::cxx::parser::non_validating::non_negative_integer_pskel< char > non_negative_integer_pskel;
  typedef ::xsd::cxx::parser::non_validating::non_negative_integer_pimpl< char > non_negative_integer_pimpl;

  typedef ::xsd::cxx::parser::non_validating::positive_integer_pskel< char > positive_integer_pskel;
  typedef ::xsd::cxx::parser::non_validating::positive_integer_pimpl< char > positive_integer_pimpl;

  typedef ::xsd::cxx::parser::non_validating::negative_integer_pskel< char > negative_integer_pskel;
  typedef ::xsd::cxx::parser::non_validating::negative_integer_pimpl< char > negative_integer_pimpl;

  typedef ::xsd::cxx::parser::non_validating::boolean_pskel< char > boolean_pskel;
  typedef ::xsd::cxx::parser::non_validating::boolean_pimpl< char > boolean_pimpl;

  typedef ::xsd::cxx::parser::non_validating::float_pskel< char > float_pskel;
  typedef ::xsd::cxx::parser::non_validating::float_pimpl< char > float_pimpl;

  typedef ::xsd::cxx::parser::non_validating::double_pskel< char > double_pskel;
  typedef ::xsd::cxx::parser::non_validating::double_pimpl< char > double_pimpl;

  typedef ::xsd::cxx::parser::non_validating::decimal_pskel< char > decimal_pskel;
  typedef ::xsd::cxx::parser::non_validating::decimal_pimpl< char > decimal_pimpl;

  typedef ::xsd::cxx::parser::non_validating::string_pskel< char > string_pskel;
  typedef ::xsd::cxx::parser::non_validating::string_pimpl< char > string_pimpl;

  typedef ::xsd::cxx::parser::non_validating::normalized_string_pskel< char > normalized_string_pskel;
  typedef ::xsd::cxx::parser::non_validating::normalized_string_pimpl< char > normalized_string_pimpl;

  typedef ::xsd::cxx::parser::non_validating::token_pskel< char > token_pskel;
  typedef ::xsd::cxx::parser::non_validating::token_pimpl< char > token_pimpl;

  typedef ::xsd::cxx::parser::non_validating::name_pskel< char > name_pskel;
  typedef ::xsd::cxx::parser::non_validating::name_pimpl< char > name_pimpl;

  typedef ::xsd::cxx::parser::non_validating::nmtoken_pskel< char > nmtoken_pskel;
  typedef ::xsd::cxx::parser::non_validating::nmtoken_pimpl< char > nmtoken_pimpl;

  typedef ::xsd::cxx::parser::non_validating::nmtokens_pskel< char > nmtokens_pskel;
  typedef ::xsd::cxx::parser::non_validating::nmtokens_pimpl< char > nmtokens_pimpl;

  typedef ::xsd::cxx::parser::non_validating::ncname_pskel< char > ncname_pskel;
  typedef ::xsd::cxx::parser::non_validating::ncname_pimpl< char > ncname_pimpl;

  typedef ::xsd::cxx::parser::non_validating::language_pskel< char > language_pskel;
  typedef ::xsd::cxx::parser::non_validating::language_pimpl< char > language_pimpl;

  typedef ::xsd::cxx::parser::non_validating::id_pskel< char > id_pskel;
  typedef ::xsd::cxx::parser::non_validating::id_pimpl< char > id_pimpl;

  typedef ::xsd::cxx::parser::non_validating::idref_pskel< char > idref_pskel;
  typedef ::xsd::cxx::parser::non_validating::idref_pimpl< char > idref_pimpl;

  typedef ::xsd::cxx::parser::non_validating::idrefs_pskel< char > idrefs_pskel;
  typedef ::xsd::cxx::parser::non_validating::idrefs_pimpl< char > idrefs_pimpl;

  typedef ::xsd::cxx::parser::non_validating::uri_pskel< char > uri_pskel;
  typedef ::xsd::cxx::parser::non_validating::uri_pimpl< char > uri_pimpl;

  typedef ::xsd::cxx::parser::non_validating::qname_pskel< char > qname_pskel;
  typedef ::xsd::cxx::parser::non_validating::qname_pimpl< char > qname_pimpl;

  typedef ::xsd::cxx::parser::non_validating::base64_binary_pskel< char > base64_binary_pskel;
  typedef ::xsd::cxx::parser::non_validating::base64_binary_pimpl< char > base64_binary_pimpl;

  typedef ::xsd::cxx::parser::non_validating::hex_binary_pskel< char > hex_binary_pskel;
  typedef ::xsd::cxx::parser::non_validating::hex_binary_pimpl< char > hex_binary_pimpl;

  typedef ::xsd::cxx::parser::non_validating::date_pskel< char > date_pskel;
  typedef ::xsd::cxx::parser::non_validating::date_pimpl< char > date_pimpl;

  typedef ::xsd::cxx::parser::non_validating::date_time_pskel< char > date_time_pskel;
  typedef ::xsd::cxx::parser::non_validating::date_time_pimpl< char > date_time_pimpl;

  typedef ::xsd::cxx::parser::non_validating::duration_pskel< char > duration_pskel;
  typedef ::xsd::cxx::parser::non_validating::duration_pimpl< char > duration_pimpl;

  typedef ::xsd::cxx::parser::non_validating::gday_pskel< char > gday_pskel;
  typedef ::xsd::cxx::parser::non_validating::gday_pimpl< char > gday_pimpl;

  typedef ::xsd::cxx::parser::non_validating::gmonth_pskel< char > gmonth_pskel;
  typedef ::xsd::cxx::parser::non_validating::gmonth_pimpl< char > gmonth_pimpl;

  typedef ::xsd::cxx::parser::non_validating::gmonth_day_pskel< char > gmonth_day_pskel;
  typedef ::xsd::cxx::parser::non_validating::gmonth_day_pimpl< char > gmonth_day_pimpl;

  typedef ::xsd::cxx::parser::non_validating::gyear_pskel< char > gyear_pskel;
  typedef ::xsd::cxx::parser::non_validating::gyear_pimpl< char > gyear_pimpl;

  typedef ::xsd::cxx::parser::non_validating::gyear_month_pskel< char > gyear_month_pskel;
  typedef ::xsd::cxx::parser::non_validating::gyear_month_pimpl< char > gyear_month_pimpl;

  typedef ::xsd::cxx::parser::non_validating::time_pskel< char > time_pskel;
  typedef ::xsd::cxx::parser::non_validating::time_pimpl< char > time_pimpl;

  // Exceptions. See libxsd/xsd/cxx/parser/exceptions.hxx for details.
  //
  typedef ::xsd::cxx::parser::exception< char > exception;

  // Parsing diagnostics.
  //
  typedef ::xsd::cxx::parser::severity severity;
  typedef ::xsd::cxx::parser::error< char > error;
  typedef ::xsd::cxx::parser::diagnostics< char > diagnostics;
  typedef ::xsd::cxx::parser::parsing< char > parsing;

  // Error handler. See libxsd/xsd/cxx/xml/error-handler.hxx for details.
  //
  typedef ::xsd::cxx::xml::error_handler< char > error_handler;

  // Read-only string.
  //
  typedef ::xsd::cxx::ro_string< char > ro_string;

  // Parsing flags. See libxsd/xsd/cxx/parser/xerces/elements.hxx
  // for details.
  //
  typedef ::xsd::cxx::parser::xerces::flags flags;

  // Parsing properties. See libxsd/xsd/cxx/parser/xerces/elements.hxx
  // for details.
  //
  typedef ::xsd::cxx::parser::xerces::properties< char > properties;

  // Document type. See libxsd/xsd/cxx/parser/xerces/elements.hxx
  // for details.
  //
  typedef ::xsd::cxx::parser::xerces::document< char > document;
}

class double_vector_pskel: public ::xml_schema::complex_content
{
  public:
  // Parser callbacks. Override them in your implementation.
  //
  // virtual void
  // pre ();

  virtual void
  x (const ::std::string&);

  virtual void
  y (const ::std::string&);

  virtual void
  z (const ::std::string&);

  virtual void
  post_double_vector ();

  // Parser construction API.
  //
  void
  x_parser (::xml_schema::string_pskel&);

  void
  y_parser (::xml_schema::string_pskel&);

  void
  z_parser (::xml_schema::string_pskel&);

  void
  parsers (::xml_schema::string_pskel& /* x */,
           ::xml_schema::string_pskel& /* y */,
           ::xml_schema::string_pskel& /* z */);

  // Constructor.
  //
  double_vector_pskel ();

  // Implementation.
  //
  protected:
  virtual bool
  _start_element_impl (const ::xml_schema::ro_string&,
                       const ::xml_schema::ro_string&,
                       const ::xml_schema::ro_string*);

  virtual bool
  _end_element_impl (const ::xml_schema::ro_string&,
                     const ::xml_schema::ro_string&);

  protected:
  ::xml_schema::string_pskel* x_parser_;
  ::xml_schema::string_pskel* y_parser_;
  ::xml_schema::string_pskel* z_parser_;
};

class integer_vector_pskel: public ::xml_schema::complex_content
{
  public:
  // Parser callbacks. Override them in your implementation.
  //
  // virtual void
  // pre ();

  virtual void
  x (const ::std::string&);

  virtual void
  y (const ::std::string&);

  virtual void
  z (const ::std::string&);

  virtual void
  post_integer_vector ();

  // Parser construction API.
  //
  void
  x_parser (::xml_schema::string_pskel&);

  void
  y_parser (::xml_schema::string_pskel&);

  void
  z_parser (::xml_schema::string_pskel&);

  void
  parsers (::xml_schema::string_pskel& /* x */,
           ::xml_schema::string_pskel& /* y */,
           ::xml_schema::string_pskel& /* z */);

  // Constructor.
  //
  integer_vector_pskel ();

  // Implementation.
  //
  protected:
  virtual bool
  _start_element_impl (const ::xml_schema::ro_string&,
                       const ::xml_schema::ro_string&,
                       const ::xml_schema::ro_string*);

  virtual bool
  _end_element_impl (const ::xml_schema::ro_string&,
                     const ::xml_schema::ro_string&);

  protected:
  ::xml_schema::string_pskel* x_parser_;
  ::xml_schema::string_pskel* y_parser_;
  ::xml_schema::string_pskel* z_parser_;
};

class cuboid_pskel: public ::xml_schema::complex_content
{
  public:
  // Parser callbacks. Override them in your implementation.
  //
  // virtual void
  // pre ();

  virtual void
  coordinates ();

  virtual void
  particles_per_dimension ();

  virtual void
  distance_particles (const ::std::string&);

  virtual void
  mass (const ::std::string&);

  virtual void
  velocity ();

  virtual void
  post_cuboid ();

  // Parser construction API.
  //
  void
  coordinates_parser (::double_vector_pskel&);

  void
  particles_per_dimension_parser (::integer_vector_pskel&);

  void
  distance_particles_parser (::xml_schema::string_pskel&);

  void
  mass_parser (::xml_schema::string_pskel&);

  void
  velocity_parser (::double_vector_pskel&);

  void
  parsers (::double_vector_pskel& /* coordinates */,
           ::integer_vector_pskel& /* particles_per_dimension */,
           ::xml_schema::string_pskel& /* distance_particles */,
           ::xml_schema::string_pskel& /* mass */,
           ::double_vector_pskel& /* velocity */);

  // Constructor.
  //
  cuboid_pskel ();

  // Implementation.
  //
  protected:
  virtual bool
  _start_element_impl (const ::xml_schema::ro_string&,
                       const ::xml_schema::ro_string&,
                       const ::xml_schema::ro_string*);

  virtual bool
  _end_element_impl (const ::xml_schema::ro_string&,
                     const ::xml_schema::ro_string&);

  protected:
  ::double_vector_pskel* coordinates_parser_;
  ::integer_vector_pskel* particles_per_dimension_parser_;
  ::xml_schema::string_pskel* distance_particles_parser_;
  ::xml_schema::string_pskel* mass_parser_;
  ::double_vector_pskel* velocity_parser_;
};

class cuboid_cluster_pskel: public ::xml_schema::complex_content
{
  public:
  // Parser callbacks. Override them in your implementation.
  //
  // virtual void
  // pre ();

  virtual void
  cuboid ();

  virtual void
  post_cuboid_cluster ();

  // Parser construction API.
  //
  void
  cuboid_parser (::cuboid_pskel&);

  void
  parsers (::cuboid_pskel& /* cuboid */);

  // Constructor.
  //
  cuboid_cluster_pskel ();

  // Implementation.
  //
  protected:
  virtual bool
  _start_element_impl (const ::xml_schema::ro_string&,
                       const ::xml_schema::ro_string&,
                       const ::xml_schema::ro_string*);

  virtual bool
  _end_element_impl (const ::xml_schema::ro_string&,
                     const ::xml_schema::ro_string&);

  protected:
  ::cuboid_pskel* cuboid_parser_;
};

class particle_pskel: public ::xml_schema::complex_content
{
  public:
  // Parser callbacks. Override them in your implementation.
  //
  // virtual void
  // pre ();

  virtual void
  coordinates ();

  virtual void
  velocity ();

  virtual void
  mass (const ::std::string&);

  virtual void
  post_particle ();

  // Parser construction API.
  //
  void
  coordinates_parser (::double_vector_pskel&);

  void
  velocity_parser (::double_vector_pskel&);

  void
  mass_parser (::xml_schema::string_pskel&);

  void
  parsers (::double_vector_pskel& /* coordinates */,
           ::double_vector_pskel& /* velocity */,
           ::xml_schema::string_pskel& /* mass */);

  // Constructor.
  //
  particle_pskel ();

  // Implementation.
  //
  protected:
  virtual bool
  _start_element_impl (const ::xml_schema::ro_string&,
                       const ::xml_schema::ro_string&,
                       const ::xml_schema::ro_string*);

  virtual bool
  _end_element_impl (const ::xml_schema::ro_string&,
                     const ::xml_schema::ro_string&);

  protected:
  ::double_vector_pskel* coordinates_parser_;
  ::double_vector_pskel* velocity_parser_;
  ::xml_schema::string_pskel* mass_parser_;
};

class particle_cluster_pskel: public ::xml_schema::complex_content
{
  public:
  // Parser callbacks. Override them in your implementation.
  //
  // virtual void
  // pre ();

  virtual void
  particle ();

  virtual void
  post_particle_cluster ();

  // Parser construction API.
  //
  void
  particle_parser (::particle_pskel&);

  void
  parsers (::particle_pskel& /* particle */);

  // Constructor.
  //
  particle_cluster_pskel ();

  // Implementation.
  //
  protected:
  virtual bool
  _start_element_impl (const ::xml_schema::ro_string&,
                       const ::xml_schema::ro_string&,
                       const ::xml_schema::ro_string*);

  virtual bool
  _end_element_impl (const ::xml_schema::ro_string&,
                     const ::xml_schema::ro_string&);

  protected:
  ::particle_pskel* particle_parser_;
};

class input_particles_pskel: public ::xml_schema::complex_content
{
  public:
  // Parser callbacks. Override them in your implementation.
  //
  // virtual void
  // pre ();

  virtual void
  particle_file (const ::std::string&);

  virtual void
  cuboids_file (const ::std::string&);

  virtual void
  cuboids ();

  virtual void
  particles ();

  virtual void
  post_input_particles ();

  // Parser construction API.
  //
  void
  particle_file_parser (::xml_schema::string_pskel&);

  void
  cuboids_file_parser (::xml_schema::string_pskel&);

  void
  cuboids_parser (::cuboid_cluster_pskel&);

  void
  particles_parser (::particle_cluster_pskel&);

  void
  parsers (::xml_schema::string_pskel& /* particle_file */,
           ::xml_schema::string_pskel& /* cuboids_file */,
           ::cuboid_cluster_pskel& /* cuboids */,
           ::particle_cluster_pskel& /* particles */);

  // Constructor.
  //
  input_particles_pskel ();

  // Implementation.
  //
  protected:
  virtual bool
  _start_element_impl (const ::xml_schema::ro_string&,
                       const ::xml_schema::ro_string&,
                       const ::xml_schema::ro_string*);

  virtual bool
  _end_element_impl (const ::xml_schema::ro_string&,
                     const ::xml_schema::ro_string&);

  protected:
  ::xml_schema::string_pskel* particle_file_parser_;
  ::xml_schema::string_pskel* cuboids_file_parser_;
  ::cuboid_cluster_pskel* cuboids_parser_;
  ::particle_cluster_pskel* particles_parser_;
};

class molsimInput_pskel: public ::xml_schema::complex_content
{
  public:
  // Parser callbacks. Override them in your implementation.
  //
  // virtual void
  // pre ();

  virtual void
  name_output (const ::std::string&);

  virtual void
  frequency_output (const ::std::string&);

  virtual void
  delta_t (const ::std::string&);

  virtual void
  t_end (const ::std::string&);

  virtual void
  particles ();

  virtual void
  post_molsimInput ();

  // Parser construction API.
  //
  void
  name_output_parser (::xml_schema::string_pskel&);

  void
  frequency_output_parser (::xml_schema::string_pskel&);

  void
  delta_t_parser (::xml_schema::string_pskel&);

  void
  t_end_parser (::xml_schema::string_pskel&);

  void
  particles_parser (::input_particles_pskel&);

  void
  parsers (::xml_schema::string_pskel& /* name_output */,
           ::xml_schema::string_pskel& /* frequency_output */,
           ::xml_schema::string_pskel& /* delta_t */,
           ::xml_schema::string_pskel& /* t_end */,
           ::input_particles_pskel& /* particles */);

  // Constructor.
  //
  molsimInput_pskel ();

  // Implementation.
  //
  protected:
  virtual bool
  _start_element_impl (const ::xml_schema::ro_string&,
                       const ::xml_schema::ro_string&,
                       const ::xml_schema::ro_string*);

  virtual bool
  _end_element_impl (const ::xml_schema::ro_string&,
                     const ::xml_schema::ro_string&);

  protected:
  ::xml_schema::string_pskel* name_output_parser_;
  ::xml_schema::string_pskel* frequency_output_parser_;
  ::xml_schema::string_pskel* delta_t_parser_;
  ::xml_schema::string_pskel* t_end_parser_;
  ::input_particles_pskel* particles_parser_;
};

#include <xsd/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.

#endif // MOLSIM_INPUT_PSKEL_HXX
