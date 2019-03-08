#include <gtest/gtest.h>

#include "glm/glm.hpp"
#include "lsg/math/AABB.h"
#include "lsg/math/Ray.h"

using namespace lsg;

template <typename T>
void expectNear(const glm::tvec3<T>& actual, const glm::tvec3<T>& expected, T epsilon) {
	EXPECT_NEAR(actual.x, expected.x, epsilon);
	EXPECT_NEAR(actual.y, expected.y, epsilon);
	EXPECT_NEAR(actual.z, expected.z, epsilon);
}

TEST(Ray, IntersectionAABB) {
	{
		AABB<float> box({ 0, 0, 0 }, { 5, 5, 5 });
		glm::tvec3<float> origin{ 0, 0, 6 };
		glm::tvec3<float> dir = glm::normalize(glm::tvec3<float>(6, 6, 6) - origin);

		Ray<float> ray(origin, dir);

		EXPECT_FALSE(ray.intersectAABB(box));
	}

	{
		AABB<float> box({ 0, 0, 0 }, { 5, 5, 5 });
		glm::tvec3<float> origin{ 0, 0, -1 };
		glm::tvec3<float> dir = glm::normalize(glm::tvec3<float>(7, 7, 7) - origin);

		Ray<float> ray(origin, dir);

		EXPECT_TRUE(ray.intersectAABB(box));
	}

	{
		AABB<float> box({ 0, 0, 0 }, { 5, 5, 5 });
		glm::tvec3<float> origin{ 1, 1, 1 };
		glm::tvec3<float> dir = glm::normalize(glm::tvec3<float>(7, 7, 7) - origin);

		Ray<float> ray(origin, dir);

		EXPECT_TRUE(ray.intersectAABB(box));
	}

	{
		AABB<float> box({ 0, 0, 0 }, { 5, 5, 5 });
		glm::tvec3<float> origin{ -1, -1, -1 };
		glm::tvec3<float> dir = glm::normalize(glm::tvec3<float>(7, 7, 7) - origin);

		Ray<float> ray(origin, dir);

		EXPECT_TRUE(ray.intersectAABB(box));
	}

	//EXPECT_TRUE()
}

TEST(Ray, IntersectionTriangle) {
	{
		glm::tvec3<float> a{ 0, 0,0 };
		glm::tvec3<float> b{ 0, 5, 0 };
		glm::tvec3<float> c{ 5, 0, 0 };

		glm::tvec3<float> origin{ -1, 0, -1 };
		glm::tvec3<float> dir = glm::normalize(glm::tvec3<float>(1, 1, 0) - origin);
		Ray<float> ray(origin, dir);

		glm::tvec3<float> expected{ 1,1,0 };

		std::optional<glm::tvec3<float>> isect = ray.intersectTriangle(a, b, c);
		ASSERT_TRUE(isect.has_value());
		expectNear(isect.value(), expected, 0.001f);
	}

	{
		glm::tvec3<float> a{ 0, 0,0 };
		glm::tvec3<float> b{ 0, 5, 0 };
		glm::tvec3<float> c{ 5, 0, 0 };

		glm::tvec3<float> origin{ -1, 0, 1 };
		glm::tvec3<float> dir = glm::normalize(glm::tvec3<float>(1, 1, 0) - origin);
		Ray<float> ray(origin, dir);

		glm::tvec3<float> expected{ 1,1,0 };

		std::optional<glm::tvec3<float>> isect = ray.intersectTriangle(a, b, c);
		ASSERT_TRUE(isect.has_value());
		expectNear(isect.value(), expected, 0.001f);
	}
    
	{
		glm::tvec3<float> a{ 0, 0,0 };
		glm::tvec3<float> b{ 0, 5, 0 };
		glm::tvec3<float> c{ 5, 0, 0 };

		glm::tvec3<float> origin{ 0, 10, -10 };
		glm::tvec3<float> dir = glm::normalize(glm::tvec3<float>(-10, 0, 0) - origin);
		Ray<float> ray(origin, dir);

		std::optional<glm::tvec3<float>> isect = ray.intersectTriangle(a, b, c);
		EXPECT_FALSE(isect.has_value());
	}
}