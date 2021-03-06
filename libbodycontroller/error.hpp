/**
 * This file is part of libbodycontroller.
 *
 * (c) Mathias Dalheimer <md@gonium.net>, 2012
 *
 * libbodycontroller is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * libbodycontroller is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libbodycontroller. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef LIBFULLCIRCLE_ERROR_HPP
#define LIBFULLCIRCLE_ERROR_HPP 1

#include <string>
#include <exception>

namespace bodycontroller {
  class GenericException : public std::exception {
	public:
	  typedef boost::shared_ptr<GenericException> Ptr;
	  GenericException (const std::string reason) : _reason(reason) {};
	  virtual ~GenericException() throw() {};
	  virtual const char* what() const throw() { return reason().c_str(); }
	  virtual const std::string& reason() const { return _reason; }

	private:
	  std::string _reason;
  };

  class CommunicationException : public GenericException{
	public:
	  typedef boost::shared_ptr<CommunicationException> Ptr;
	  CommunicationException (const std::string reason) :
		bodycontroller::GenericException(reason) {};
	  virtual ~CommunicationException() throw() {};

  };
  
  class DataFormatException : public GenericException{
	public:
	  typedef boost::shared_ptr<DataFormatException> Ptr;
	  DataFormatException (const std::string reason) :
		bodycontroller::GenericException(reason) {};
	  virtual ~DataFormatException() throw() {};

  };

  class IndexOutOfBoundException : public GenericException{
	public:
	  typedef boost::shared_ptr<IndexOutOfBoundException> Ptr;
	  IndexOutOfBoundException (const std::string reason) :
		bodycontroller::GenericException(reason) {};
	  virtual ~IndexOutOfBoundException() throw() {};

  };


  class StoreException : public GenericException{
	public:
	  typedef boost::shared_ptr<StoreException> Ptr;
	  StoreException (const std::string reason) :
		bodycontroller::GenericException(reason) {};
	  virtual ~StoreException() throw() {};
  };
	
	class RenderException : public GenericException {
	public:
		typedef boost::shared_ptr<RenderException> Ptr;
		RenderException (const std::string reason) :
		bodycontroller::GenericException(reason) {};
		virtual ~RenderException() throw() {};	
	};

}

#endif /* LIBFULLCIRCLE_ERROR_HPP */
