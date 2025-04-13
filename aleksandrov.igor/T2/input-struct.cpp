#include "input-struct.hpp"

namespace aleksandrov
{
  namespace detail
  {
    std::istream& operator>>(std::istream& in, DelimeterI&& dest)
    {
      std::istream::sentry sentry(in);
      if (!sentry)
      {
        return in;
      }
      char c = '\0';
      in >> c;
      if (in && c != dest.exp)
      {
        in.setstate(std::ios::failbit);
      }
      return in;
    }

    std::istream& operator>>(std::istream& in, DoubleI&& dest)
    {
      std::istream::sentry sentry(in);
      if (!sentry)
      {
        return in;
      }
      return in >> dest.ref >> DelimeterI{ 'd' };
    }

    std::istream& operator>>(std::istream& in, RationalI&& dest)
    {
      std::istream::sentry sentry(in);
      if (!sentry)
      {
        return in;
      }
      in >> DelimeterI{ '(' } >> DelimeterI{ ':' };
      in >> DelimeterI{ 'N' } >> LongLongI{ dest.ref.first };
      in >> DelimeterI{ ':' };
      in >> DelimeterI{ 'D' } >> UnsignedLongLongI{ dest.ref.second };
      in >> DelimeterI{ ':' } >> DelimeterI{ ')' };
      return in;
    }

    std::istream& operator>>(std::istream& in, LongLongI&& dest)
    {
      std::istream::sentry sentry(in);
      if (!sentry)
      {
        return in;
      }
      return in >> dest.ref;
    }

    std::istream& operator>>(std::istream& in, UnsignedLongLongI&& dest)
    {
      std::istream::sentry sentry(in);
      if (!sentry)
      {
        return in;
      }
      return in >> dest.ref;
    }

    std::istream& operator>>(std::istream& in, StringI&& dest)
    {
      std::istream::sentry sentry(in);
      if (!sentry)
      {
        return in;
      }
      return std::getline(in >> DelimeterI{ '"' }, dest.ref, '"');
    }
  }

  std::istream& operator>>(std::istream& in, DataStruct& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    DataStruct input;
    {
      in >> detail::DelimeterI{ '(' } >> detail::DelimeterI{ ':' };
      for (size_t i = 0; i < 3; ++i)
      {
        std::string key;
        in >> key;
        if (key == "key1")
        {
          in >> detail::DoubleI{ input.key1 };
        }
        else if (key == "key2")
        {
          in >> detail::RationalI{ input.key2 };
        }
        else if (key == "key3")
        {
          in >> detail::StringI{ input.key3 };
        }
        in >> detail::DelimeterI{ ':' };
      }
      in >> detail::DelimeterI{ ')' };
    }
    if (in)
    {
      dest = input;
    }
    return in;
  }
}

