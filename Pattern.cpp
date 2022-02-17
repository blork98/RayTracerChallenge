#include "Pattern.h"
#include "Constants.h"
#include "GeometricObject.h"

#include <cmath>

namespace RTC
{
	Pattern::Pattern()
		:transform(std::make_shared<Transform>())
	{}

	Pattern::Pattern(const Pattern& pat)
		:transform(pat.transform)
	{}

	Pattern::~Pattern()
	{}

	Pattern& Pattern::operator=(const Pattern& rhs)
	{
		if (this == &rhs)
			return (*this);

		transform = rhs.transform;

		return (*this);
	}

	void Pattern::set_transform(std::shared_ptr<Transform> trans)
	{
		transform = trans;
	}

	std::shared_ptr<Transform> Pattern::get_transform()
	{
		return transform;
	}

	Color Pattern::pattern_at_object(Tuple point, ShadeInfo& s) const
	{
		Tuple object_point = s.object->get_transform()->apply_inverse_transform(point);
		Tuple pattern_point = transform->apply_inverse_transform(object_point);
		return pattern_at(pattern_point);
	}

	///////////////////////////////////////// Radial Gradient //////////////////////////
	RadialGradient::RadialGradient()
		:Pattern(), a(White), b(Black)
	{}

	RadialGradient::RadialGradient(const Color& a_, const Color& b_)
		: Pattern(), a(a_), b(b_)
	{}

	RadialGradient::RadialGradient(const RadialGradient& pat)
		: Pattern(pat), a(pat.a), b(pat.b)
	{}

	RadialGradient::~RadialGradient()
	{}

	Pattern& RadialGradient::operator=(const RadialGradient& rhs)
	{
		if (this == &rhs)
			return (*this);

		Pattern::operator=(rhs);
		a = rhs.a;
		b = rhs.b;

		return (*this);
	}

	Color RadialGradient::pattern_at(Tuple point) const
	{
		double sq = std::floor(std::sqrt(point.x*point.x + point.z*point.z));

		Color distance = b - a;
		double fraction = point.x - std::floor(point.x);
		Color res = a + fraction*distance;

		if (((int)sq % 2) == 0)
		{
			Color distance = b - a;
			double fraction = point.x - std::floor(point.x);
			Color res = a + fraction*distance;
			return res;
		}
		else
		{
			Color distance = a - b;
			double fraction = point.x - std::floor(point.x);
			Color res = b + fraction*distance;
			return res;
		}
	}

	///////////////////////////////////////// Checker //////////////////////////////////
	CheckerPattern::CheckerPattern()
		:Pattern(), a(White), b(Black)
	{}

	CheckerPattern::CheckerPattern(Color a_, Color b_)
		: Pattern(), a(a_), b(b_)
	{}

	CheckerPattern::CheckerPattern(const CheckerPattern& pat)
		: Pattern(pat), a(pat.a), b(pat.b)
	{}

	CheckerPattern::~CheckerPattern()
	{}

	Pattern& CheckerPattern::operator=(const CheckerPattern& rhs)
	{
		if (this == &rhs)
			return (*this);

		Pattern::operator=(rhs);
		a = rhs.a;
		b = rhs.b;

		return (*this);
	}

	Color CheckerPattern::pattern_at(Tuple point) const
	{
		int x = (int)std::floor(point.x);
		int y = (int)std::floor(point.y);
		int z = (int)std::floor(point.z);
		int sum = x + y + z;

		if ((sum % 2) == 0)
			return a;
		else
			return b;
	}

	RingPattern::RingPattern()
		:Pattern(), a(White), b(Black)
	{}

	RingPattern::RingPattern(Color a_, Color b_)
		: Pattern(), a(a_), b(b_)
	{}

	RingPattern::RingPattern(const RingPattern& pat)
		: Pattern(pat), a(pat.a), b(pat.b)
	{}

	RingPattern::~RingPattern()
	{}

	Pattern& RingPattern::operator=(const RingPattern& rhs)
	{
		if (this == &rhs)
			return (*this);

		Pattern::operator=(rhs);
		a = rhs.a;
		b = rhs.b;

		return (*this);
	}

	Color RingPattern::pattern_at(Tuple point) const
	{
		double sq = std::floor(std::sqrt(point.x*point.x + point.z*point.z));
		
		if (((int)sq % 2) == 0)
			return a;
		else
			return b;
	}

	GradientPattern::GradientPattern()
		:Pattern(), a(White), b(Black)
	{}

	GradientPattern::GradientPattern(Color a_, Color b_)
		: Pattern(), a(a_), b(b_)
	{}

	GradientPattern::GradientPattern(const GradientPattern& pat)
		: Pattern(pat), a(pat.a), b(pat.b)
	{}

	GradientPattern::~GradientPattern()
	{}

	Pattern& GradientPattern::operator=(const GradientPattern& rhs)
	{
		if (this == &rhs)
			return (*this);

		Pattern::operator=(rhs);
		a = rhs.a;
		b = rhs.b;

		return (*this);
	}

	Color GradientPattern::pattern_at(Tuple point) const
	{
		Color distance = b - a;
		double fraction = point.x - std::floor(point.x);
		Color res = a + fraction*distance;
		return res;
	}

	StripePattern::StripePattern()
		:Pattern(),a(White), b(Black)
	{}

	StripePattern::StripePattern(const Color& a_, const Color&b_)
		: Pattern(), a(a_), b(b_)
	{}

	StripePattern::StripePattern(const StripePattern& pat)
		:Pattern(pat),a(pat.a),b(pat.b)
	{}

	StripePattern::~StripePattern()
	{}

	StripePattern& StripePattern::operator=(const StripePattern& rhs)
	{
		if (this == &rhs)
			return (*this);

		Pattern::operator=(rhs);
		a = rhs.a;
		b = rhs.b;
		
		return (*this);
	}

	Color StripePattern::pattern_at(Tuple point) const
	{
		if ( ( ((int)std::floor(point.x)) % 2) == 0)
			return a;
		else
			return b;
	}
}

