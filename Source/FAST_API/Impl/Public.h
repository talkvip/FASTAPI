#ifndef HUNDSUN_PUBLIC_OS
#define HUNDSUN_PUBLIC_OS

#if _WIN32
# if !defined (snprintf)
#   define snprintf _snprintf
# endif
#endif

template <class T>
class Release_Guard
{
public:
  Release_Guard (T* lpObj)
    : m_lpObj (lpObj)
  {}

  ~Release_Guard ()
  {
    if (this->m_lpObj)
      this->m_lpObj->Release () ;
  }

  void Reset ()
  {
    this->m_lpObj = 0 ;
  }

protected:
  T*                     m_lpObj ;
} ;

template <class T>
class Delete_Guard
{
public:
  Delete_Guard (T* lpObj)
    : m_lpObj (lpObj)
  {}

  ~Delete_Guard ()
  {
    if (this->m_lpObj)
      delete this->m_lpObj ;
  }

  void Reset ()
  {
    this->m_lpObj = 0 ;
  }

protected:
  T*                     m_lpObj ;
} ;

#endif