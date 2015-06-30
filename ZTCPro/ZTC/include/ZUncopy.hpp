#ifndef ZTC__Include__ZUncopy_hpp
#define ZTC__Include__ZUncopy_hpp

class ZUncopy
{
protected:
	ZUncopy()
	{}
	virtual ~ZUncopy()
	{}

private:
	ZUncopy(const ZUncopy&);
	ZUncopy& operator = (const ZUncopy&);
};

#endif //ZTC__Include__ZUncopy_hpp
