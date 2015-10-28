#include <iterator>
#include "parser.h"

frmiterator::frmiterator(void)
{
	return;
}

frmiterator::frmiterator(fldformat *iwildcard, std::map<int,fldformat>::iterator iit, std::map<int,fldformat>::iterator ibegin, std::map<int,fldformat>::iterator iend, int icurnum) :
	wildcard(iwildcard),
	it(iit),
	begin(ibegin),
	end(iend),
	curnum(icurnum),
	next(iit==iend?iend:++iit)
{
	while(it!=end && it->first<0)
		++it;
	return;
}

frmiterator::frmiterator(const frmiterator &it) :
	wildcard(it.wildcard),
	it(it.it),
	next(it.next),
	begin(it.begin),
	end(it.end),
	tmpmap(it.tmpmap),
	curnum(it.curnum)
{
	return;
}

frmiterator::~frmiterator(void)
{
	return;
}

frmiterator& frmiterator::operator=(const frmiterator &other)
{
	wildcard=other.wildcard;
	it=other.it;
	next=other.next;
	begin=other.begin;
	end=other.end;
	tmpmap=other.tmpmap;
	curnum=other.curnum;
}

bool frmiterator::operator!=(frmiterator const &other) const
{
	return it!=other.it || curnum!=other.curnum;
}

bool frmiterator::operator==(frmiterator const &other) const
{
	return it==other.it && curnum==other.curnum;
}

pair<const int, fldformat>& frmiterator::operator*(void)
{
	if(!wildcard||it->first==curnum||curnum<0)
		return *it;
	else
	{
		tmpmap[curnum].copyFrom(*wildcard); //construct a temporary map of the missing references
		return *tmpmap.find(curnum);
	}
}

pair<const int, fldformat>* frmiterator::operator->(void)
{
	return &(*(*this));
}

frmiterator& frmiterator::operator++(void)
{
	if(!wildcard)
	{
		++it;
		return *this;
	}

	++curnum;

	if(next!=end && curnum==next->first)
	{
		it=next;
		++next;
	}
	return *this;
}

frmiterator& frmiterator::operator--(void)
{
	if(!wildcard)
	{
		--it;
		return *this;
	}

	if(it!=end && curnum==it->first)
	{
		next=it;
		--it;
	}

	--curnum;

	return *this;
}