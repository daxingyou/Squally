#include "SpriterAnimationTimelineEventMainline.h"

#include "cocos/2d/CCSprite.h"

using namespace cocos2d;

SpriterAnimationTimelineEventMainline* SpriterAnimationTimelineEventMainline::create(SpriterAnimationNode* animations, const SpriterMainlineKey& mainlineData, float endTime)
{
	SpriterAnimationTimelineEventMainline* instance = new SpriterAnimationTimelineEventMainline(animations, mainlineData, endTime);

	instance->autorelease();

	return instance;
}

SpriterAnimationTimelineEventMainline::SpriterAnimationTimelineEventMainline(SpriterAnimationNode* animations, const SpriterMainlineKey& mainlineData, float endTime) : super(animations, mainlineData.time, endTime)
{
	this->mainlineData = mainlineData;
}

void SpriterAnimationTimelineEventMainline::onEnter()
{
	super::onEnter();
}

float SpriterAnimationTimelineEventMainline::SampleMainlineCurve(float timeRatio)
{
	return this->SampleCurve(timeRatio, this->mainlineData.curveType, this->mainlineData.c1, this->mainlineData.c2, this->mainlineData.c3, this->mainlineData.c4);
}

float SpriterAnimationTimelineEventMainline::SampleCurve(float timeRatio, SpriterCurveType curveType, float c1, float c2, float c3, float c4)
{
	// Polynomial math
	static const auto linear = [](float a, float b, float t) { return ((b - a) * t) + a; };
	static const auto quadratic = [](float a, float b, float c, float t) { return linear(linear(a, b, t), linear(b, c, t), t); };
	static const auto cubic = [](float a, float b, float c, float d, float t) { return linear(quadratic(a, b, c, t), quadratic(b, c, d, t), t); };
	static const auto quartic = [](float a, float b, float c, float d, float e, float t) { return linear(cubic(a, b, c, d, t), cubic(b, c, d, e, t), t); };
	static const auto quintic = [](float a, float b, float c, float d, float e, float f, float t) { return linear(quartic(a, b, c, d, e, t), quartic(b, c, d, e, f, t), t); };

	// Bezier math
	static const auto solveEpsilon = [](float duration) { return 1.0f / (200.0f * duration); };
	static const auto sampleCurve = [](float a, float b, float c, float t) { return ((a * t + b) * t + c) * t; };
	static const auto sampleCurveDerivativeX = [](float ax, float bx, float cx, float t) { return (3.0f * ax * t + 2.0f * bx) * t + cx; };
	static const auto solveCurveX = [](float ax, float bx, float cx, float x, float epsilon)
	{
		float x2;
		float t2 = x;

		// First try a few iterations of Newton's method -- normally very fast.
		for (int i = 0; i < 8; i++)
		{
			x2 = sampleCurve(ax, bx, cx, t2) - x;
			
			if (std::abs(x2) < epsilon)
			{
				return t2;
			}

			float d2 = sampleCurveDerivativeX(ax, bx, cx, t2);

			if (std::abs(d2) < 1e-6f)
			{
				break;
			}

			t2 = t2 - x2 / d2;
		}

		// Fall back to the bisection method for reliability.
		float t0 = 0.0f;
		float t1 = 1.0f;
		t2 = x;

		if (t2 < t0)
		{
			return t0;
		}

		if (t2 > t1)
		{
			return t1;
		}


		while (t0 < t1)
		{
			x2 = sampleCurve(ax, bx, cx, t2);

			if (std::abs(x2 - x) < epsilon)
			{
				return t2;
			}

			if (x > x2)
			{
				t0 = t2;
			}
			else
			{
				t1 = t2;
			}

			t2 = (t1 - t0) * 0.5f + t0;
		}

		return t2; // Failure.
	};
	static const auto solve = [](float ax, float bx, float cx, float ay, float by, float cy, float x, float epsilon) { return sampleCurve(ay, by, cy, solveCurveX(ax, bx, cx, x, epsilon)); };
	static const auto bezier = [](float t, float x1, float y1, float x2, float y2)
	{
		float cx = 3.0f * x1;
		float bx = 3.0f * (x2 - x1) - cx;
		float ax = 1.0f - cx - bx;
		float cy = 3.0f * y1;
		float by = 3.0f * (y2 - y1) - cy;
		float ay = 1.0f - cy - by;

		return solve(ax, bx, cx, ay, by, cy, t, solveEpsilon(1.0f));
	};

	switch(curveType)
	{
		case SpriterCurveType::Instant:
		{
			return timeRatio >= 1.0f ? 1.0f : 0.0f;
		}
		default:
		case SpriterCurveType::Linear:
		{
			return timeRatio;
		}
		case SpriterCurveType::Quadratic:
		{
			return quadratic(0.0f, c1, 1.0f, timeRatio);
		}
		case SpriterCurveType::Cubic:
		{
			return cubic(0.0f, c1, c2, 1.0f, timeRatio);
		}
		case SpriterCurveType::Quartic:
		{
			return quartic(0.0f, c1, c2, c3, 1.0f, timeRatio);
		}
		case SpriterCurveType::Quintic:
		{
			return quintic(0.0f, c1, c2, c3, c4, 1.0f, timeRatio);
		}
		case SpriterCurveType::Bezier:
		{
			return bezier(timeRatio, c1, c2, c3, c4);
		}
	}
}

SpriterCurveType SpriterAnimationTimelineEventMainline::getCurveType()
{
	return this->mainlineData.curveType;
}

void SpriterAnimationTimelineEventMainline::onFire()
{
}
