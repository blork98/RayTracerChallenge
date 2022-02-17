#ifndef PATTERN_H_
#define PATTERN_H_

#include "Canvas.h"
#include "Transform.h"

namespace RTC
{
	struct ShadeInfo;

	class Pattern
	{
	public:
		Pattern();
		Pattern(const Pattern& pat);
		virtual ~Pattern();

		Pattern& operator=(const Pattern& rhs);

		virtual Color pattern_at_object(Tuple point, ShadeInfo& s) const;
		virtual Color pattern_at(Tuple point) const = 0;

		void set_transform(std::shared_ptr<Transform> trans);
		std::shared_ptr<Transform> get_transform();

	protected:
		std::shared_ptr<Transform> transform;
	};

	class CheckerPattern : public Pattern
	{
	public:
		CheckerPattern();
		CheckerPattern(Color a, Color b);
		CheckerPattern(const CheckerPattern& pat);
		virtual ~CheckerPattern();

		Pattern& operator=(const CheckerPattern& rhs);

		virtual Color pattern_at(Tuple point) const;

	private:
		Color a, b;
	};

	class RingPattern : public Pattern
	{
	public:
		RingPattern();
		RingPattern(Color a, Color b);
		RingPattern(const RingPattern& pat);
		virtual ~RingPattern();

		Pattern& operator=(const RingPattern& rhs);

		virtual Color pattern_at(Tuple point) const;

	private:
		Color a, b;
	};

	class GradientPattern : public Pattern
	{
	public:
		GradientPattern();
		GradientPattern(Color a, Color b);
		GradientPattern(const GradientPattern& pat);
		virtual ~GradientPattern();

		Pattern& operator=(const GradientPattern& rhs);

		virtual Color pattern_at(Tuple point) const;

	private:
		Color a, b;
	};

	class StripePattern : public Pattern
	{
	public:
		StripePattern();
		StripePattern(const Color& a, const Color&b);
		StripePattern(const StripePattern& pat);
		virtual ~StripePattern();

		StripePattern& operator=(const StripePattern& rhs);

		virtual Color pattern_at(Tuple point) const;

	private:
		Color a, b;
	};

	class RadialGradient : public Pattern
	{
	public:
		RadialGradient();
		RadialGradient(const Color& a, const Color&b);
		RadialGradient(const RadialGradient& pat);
		virtual ~RadialGradient();

		Pattern& operator=(const RadialGradient& rhs);

		virtual Color pattern_at(Tuple point) const;

	private:
		Color a, b;
	};

}

#endif