#include "stdafx.h"
#include "CppUnitTest.h"
#include "../src/StdInterface.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
#define CHECK Assert::AreEqual

namespace StdCoreTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(addShapeToFigure_test_1)
		{
			// TODO: 在此输入测试代码
			gFigure *fig = addFigure();
			ERROR_INFO info;
			gShape sh1 = { 'L', 0, 0, 1, 1 };
			gShape sh2 = { 'L', 0, 0, 0, 0 };
			gShape sh3 = { 'S', 2, 2, 3, 3 };
			gShape sh4 = { 'R', 0, 0, -1, 1 };
			gShape sh5 = { 'S', 0, 0, 1, -1 };
			gShape sh6 = { 'S', -2, 2, -3, 3 };
			gShape sh7 = { 'L', 100000, 0, -100000, 32 };
			CHECK(addShapeToFigure(fig, sh1).code == SUCCESS, true);
			CHECK(addShapeToFigure(fig, sh2).code == INVALID_LINE, true);
			CHECK(addShapeToFigure(fig, sh3).code == LINE_OVERLAP, true);
			CHECK(addShapeToFigure(fig, sh4).code == SUCCESS, true);
			CHECK(addShapeToFigure(fig, sh5).code == SUCCESS, true);
			CHECK(addShapeToFigure(fig, sh6).code == LINE_OVERLAP, true);
			CHECK(addShapeToFigure(fig, sh7).code == VALUE_OUT_OF_RANGE, true);
		}

		TEST_METHOD(addShapeToFigure_test_2)
		{
			// TODO: 在此输入测试代码
			gFigure *fig = addFigure();
			ERROR_INFO info;
			gShape sh1 = { 'C', 0, 0, 1 };
			gShape sh2 = { 'C', 0, 0, 1 };
			gShape sh3 = { 'C', 1, 0, 1 };
			gShape sh4 = { 'C', 9, 32, -32 };
			gShape sh5 = { 'C', 100000, 0, 32 };
			gShape sh6 = { 'C', 0, 100, 200000 };
			CHECK(addShapeToFigure(fig, sh1).code == SUCCESS, true);
			CHECK(addShapeToFigure(fig, sh2).code == CIRCLE_OVERLAP, true);
			CHECK(addShapeToFigure(fig, sh3).code == SUCCESS, true);
			CHECK(addShapeToFigure(fig, sh4).code == INVALID_CIRCLE, true);
			CHECK(addShapeToFigure(fig, sh5).code == VALUE_OUT_OF_RANGE, true);
			CHECK(addShapeToFigure(fig, sh6).code == VALUE_OUT_OF_RANGE, true);
		}

		TEST_METHOD(upper_lower_test_3)
		{
			// TODO: 在此输入测试代码
			gFigure *fig = addFigure();
			ERROR_INFO info;
			gShape sh1 = { 'L', 0, 0, 1, 1 };
			gShape sh2 = { 'L', 1, 0, 0, 1 };
			gShape sh3 = { 'L', 0, -1, -1, 0 };
			addShapeToFigure(fig, sh1);
			addShapeToFigure(fig, sh2);
			CHECK(fig->upperleft.x, 0.5);
			CHECK(fig->upperleft.y, 0.5);
			CHECK(fig->lowerright.x, 0.5);
			CHECK(fig->lowerright.y, 0.5);
			addShapeToFigure(fig, sh3);
			CHECK(fig->upperleft.x, -0.5);
			CHECK(fig->upperleft.y, 0.5);
			CHECK(fig->lowerright.x, 0.5);
			CHECK(fig->lowerright.y, -0.5);
			gShape sh4 = { 'L', 0, -2, -2, 0 };
			addShapeToFigure(fig, sh4);
			CHECK(fig->upperleft.x, -1.0);
			CHECK(fig->upperleft.y, 0.5);
			CHECK(fig->lowerright.x, 0.5);
			CHECK(fig->lowerright.y, -1.0);
			removeShapeByIndex(fig, 2);
			CHECK(fig->upperleft.x, -1.0);
			CHECK(fig->upperleft.y, 0.5);
			CHECK(fig->lowerright.x, 0.5);
			CHECK(fig->lowerright.y, -1.0);
			removeShapeByIndex(fig, 2);
			CHECK(fig->upperleft.x, 0.5);
			CHECK(fig->upperleft.y, 0.5);
			CHECK(fig->lowerright.x, 0.5);
			CHECK(fig->lowerright.y, 0.5);
		}

		TEST_METHOD(update_points_test)
		{
			// TODO: 在此输入测试代码
			gFigure *fig = addFigure();
			ERROR_INFO info;
			gShape sh1 = { 'L', 0, 0, 1, 1 };
			gShape sh2 = { 'L', 1, 0, 0, 1 };
			gShape sh3 = { 'L', 0, -1, -1, 0 };
			addShapeToFigure(fig, sh1);
			addShapeToFigure(fig, sh2);
			updatePoints(fig);
			CHECK(fig->points[0].x, 0.5);
			CHECK(fig->points[0].y, 0.5);
			CHECK(getPointsCount(fig), 1);
			addShapeToFigure(fig, sh3);
			CHECK(fig->points[0].x, 0.5);
			CHECK(fig->points[0].y, 0.5);
			CHECK(getPointsCount(fig), 2);
			updatePoints(fig);
			CHECK(fig->points[0].x, 0.5);
			CHECK(fig->points[0].y, 0.5);
			// CHECK(sizeof(fig->points) / sizeof(gPoint), 2u);
			CHECK(fig->points[1].x, -0.5);
			CHECK(fig->points[1].y, -0.5);
			
			gShape sh4 = { 'L', 0, -2, -2, 0 };
			addShapeToFigure(fig, sh4);
			updatePoints(fig);
			CHECK(getPointsCount(fig), 3);
			CHECK(fig->points[0].x, 0.5);
			CHECK(fig->points[0].y, 0.5);
			CHECK(fig->points[1].x, -0.5);
			CHECK(fig->points[1].y, -0.5);
			CHECK(fig->points[2].x, -1.0);
			CHECK(fig->points[2].y, -1.0);

			removeShapeByIndex(fig, 2);
			updatePoints(fig);
			CHECK(fig->points[0].x, 0.5);
			CHECK(fig->points[0].y, 0.5);
			CHECK(fig->points[1].x, -1.0);
			CHECK(fig->points[1].y, -1.0);
			CHECK(getPointsCount(fig), 2);
			removeShapeByIndex(fig, 2);
			updatePoints(fig);
			CHECK(fig->points[0].x, 0.5);
			CHECK(fig->points[0].y, 0.5);
			CHECK(getPointsCount(fig), 1);
		}

		TEST_METHOD(update_shapes)
		{
			gFigure *fig = addFigure();
			gShape sh1 = { 'L', 0, 0, 1, 1 };
			gShape sh2 = { 'C', 0 ,0, 1, 0 };
			gShape sh3 = { 'L', 0, 0, -1, 1 };
			gShape sh4 = { 'C', -1, -1, 1, 0 };
			addShapeToFigure(fig, sh1);
			addShapeToFigure(fig, sh2);
			updateShapes(fig);
			CHECK(fig->shapes[0].type, 'L');
			CHECK(fig->shapes[0].x1, 0);
			CHECK(fig->shapes[0].y1, 0);
			CHECK(fig->shapes[0].x2, 1);
			CHECK(fig->shapes[0].y2, 1);
			CHECK(fig->shapes[1].type, 'C');
			CHECK(fig->shapes[1].x1, 0);
			CHECK(fig->shapes[1].y1, 0);
			CHECK(fig->shapes[1].x2, 1);
			CHECK(fig->shapes[1].y2, 0);
			CHECK(getShapesCount(fig), 2);
			
			addShapeToFigure(fig, sh3);
			updateShapes(fig);
			CHECK(getShapesCount(fig), 3);
			CHECK(fig->shapes[0].type, 'L');
			CHECK(fig->shapes[0].x1, 0);
			CHECK(fig->shapes[0].y1, 0);
			CHECK(fig->shapes[0].x2, 1);
			CHECK(fig->shapes[0].y2, 1);
			CHECK(fig->shapes[1].type, 'C');
			CHECK(fig->shapes[1].x1, 0);
			CHECK(fig->shapes[1].y1, 0);
			CHECK(fig->shapes[1].x2, 1);
			CHECK(fig->shapes[1].y2, 0);
			CHECK(fig->shapes[2].type, 'L');
			CHECK(fig->shapes[2].x1, 0);
			CHECK(fig->shapes[2].y1, 0);
			CHECK(fig->shapes[2].x2, -1);
			CHECK(fig->shapes[2].y2, 1);
			

			addShapeToFigure(fig, sh4);
			updateShapes(fig);
			CHECK(fig->shapes[0].type, 'L');
			CHECK(fig->shapes[0].x1, 0);
			CHECK(fig->shapes[0].y1, 0);
			CHECK(fig->shapes[0].x2, 1);
			CHECK(fig->shapes[0].y2, 1);
			CHECK(fig->shapes[1].type, 'C');
			CHECK(fig->shapes[1].x1, 0);
			CHECK(fig->shapes[1].y1, 0);
			CHECK(fig->shapes[1].x2, 1);
			CHECK(fig->shapes[1].y2, 0);
			CHECK(fig->shapes[2].type, 'L');
			CHECK(fig->shapes[2].x1, 0);
			CHECK(fig->shapes[2].y1, 0);
			CHECK(fig->shapes[2].x2, -1);
			CHECK(fig->shapes[2].y2, 1);
			CHECK(fig->shapes[3].type, 'C');
			CHECK(fig->shapes[3].x1, -1);
			CHECK(fig->shapes[3].y1, -1);
			CHECK(fig->shapes[3].x2, 1);
			CHECK(fig->shapes[3].y2, 0);
			CHECK(getShapesCount(fig), 4);

			removeShapeByIndex(fig, 1);
			updateShapes(fig);
			CHECK(fig->shapes[0].type, 'L');
			CHECK(fig->shapes[0].x1, 0);
			CHECK(fig->shapes[0].y1, 0);
			CHECK(fig->shapes[0].x2, 1);
			CHECK(fig->shapes[0].y2, 1);
			CHECK(fig->shapes[1].type, 'L');
			CHECK(fig->shapes[1].x1, 0);
			CHECK(fig->shapes[1].y1, 0);
			CHECK(fig->shapes[1].x2, -1);
			CHECK(fig->shapes[1].y2, 1);
			CHECK(fig->shapes[2].type, 'C');
			CHECK(fig->shapes[2].x1, -1);
			CHECK(fig->shapes[2].y1, -1);
			CHECK(fig->shapes[2].x2, 1);
			CHECK(fig->shapes[2].y2, 0);
			CHECK(getShapesCount(fig), 3);

			removeShapeByIndex(fig, 1);
			updateShapes(fig);
			CHECK(fig->shapes[0].type, 'L');
			CHECK(fig->shapes[0].x1, 0);
			CHECK(fig->shapes[0].y1, 0);
			CHECK(fig->shapes[0].x2, 1);
			CHECK(fig->shapes[0].y2, 1);
			
			CHECK(fig->shapes[1].type, 'C');
			CHECK(fig->shapes[1].x1, -1);
			CHECK(fig->shapes[1].y1, -1);
			CHECK(fig->shapes[1].x2, 1);
			CHECK(fig->shapes[1].y2, 0);
			CHECK(getShapesCount(fig), 2);

			removeShapeByIndex(fig, 1);
			updateShapes(fig);
			CHECK(fig->shapes[0].type, 'L');
			CHECK(fig->shapes[0].x1, 0);
			CHECK(fig->shapes[0].y1, 0);
			CHECK(fig->shapes[0].x2, 1);
			CHECK(fig->shapes[0].y2, 1);

			CHECK(getShapesCount(fig), 1);
		}

		TEST_METHOD(delete_clean)
		{
			gFigure *fig = addFigure();
			gShape sh1 = { 'L', 0, 0, 1, 1 };
			gShape sh2 = { 'C', 0 ,0, 1, 0 };
			gShape sh3 = { 'L', 0, 0, -1, 1 };
			gShape sh4 = { 'C', -1, -1, 1, 0 };
			addShapeToFigure(fig, sh1);
			addShapeToFigure(fig, sh2);
			updateShapes(fig);
			CHECK(fig->shapes[0].type, 'L');
			CHECK(fig->shapes[0].x1, 0);
			CHECK(fig->shapes[0].y1, 0);
			CHECK(fig->shapes[0].x2, 1);
			CHECK(fig->shapes[0].y2, 1);
			CHECK(fig->shapes[1].type, 'C');
			CHECK(fig->shapes[1].x1, 0);
			CHECK(fig->shapes[1].y1, 0);
			CHECK(fig->shapes[1].x2, 1);
			CHECK(fig->shapes[1].y2, 0);
			CHECK(getShapesCount(fig), 2);

			addShapeToFigure(fig, sh3);
			updateShapes(fig);
			CHECK(getShapesCount(fig), 3);
			CHECK(fig->shapes[0].type, 'L');
			CHECK(fig->shapes[0].x1, 0);
			CHECK(fig->shapes[0].y1, 0);
			CHECK(fig->shapes[0].x2, 1);
			CHECK(fig->shapes[0].y2, 1);
			CHECK(fig->shapes[1].type, 'C');
			CHECK(fig->shapes[1].x1, 0);
			CHECK(fig->shapes[1].y1, 0);
			CHECK(fig->shapes[1].x2, 1);
			CHECK(fig->shapes[1].y2, 0);
			CHECK(fig->shapes[2].type, 'L');
			CHECK(fig->shapes[2].x1, 0);
			CHECK(fig->shapes[2].y1, 0);
			CHECK(fig->shapes[2].x2, -1);
			CHECK(fig->shapes[2].y2, 1);


			addShapeToFigure(fig, sh4);
			updateShapes(fig);
			CHECK(fig->shapes[0].type, 'L');
			CHECK(fig->shapes[0].x1, 0);
			CHECK(fig->shapes[0].y1, 0);
			CHECK(fig->shapes[0].x2, 1);
			CHECK(fig->shapes[0].y2, 1);
			CHECK(fig->shapes[1].type, 'C');
			CHECK(fig->shapes[1].x1, 0);
			CHECK(fig->shapes[1].y1, 0);
			CHECK(fig->shapes[1].x2, 1);
			CHECK(fig->shapes[1].y2, 0);
			CHECK(fig->shapes[2].type, 'L');
			CHECK(fig->shapes[2].x1, 0);
			CHECK(fig->shapes[2].y1, 0);
			CHECK(fig->shapes[2].x2, -1);
			CHECK(fig->shapes[2].y2, 1);
			CHECK(fig->shapes[3].type, 'C');
			CHECK(fig->shapes[3].x1, -1);
			CHECK(fig->shapes[3].y1, -1);
			CHECK(fig->shapes[3].x2, 1);
			CHECK(fig->shapes[3].y2, 0);
			CHECK(getShapesCount(fig), 4);

			removeShapeByIndex(fig, 1);
			updateShapes(fig);
			CHECK(fig->shapes[0].type, 'L');
			CHECK(fig->shapes[0].x1, 0);
			CHECK(fig->shapes[0].y1, 0);
			CHECK(fig->shapes[0].x2, 1);
			CHECK(fig->shapes[0].y2, 1);
			CHECK(fig->shapes[1].type, 'L');
			CHECK(fig->shapes[1].x1, 0);
			CHECK(fig->shapes[1].y1, 0);
			CHECK(fig->shapes[1].x2, -1);
			CHECK(fig->shapes[1].y2, 1);
			CHECK(fig->shapes[2].type, 'C');
			CHECK(fig->shapes[2].x1, -1);
			CHECK(fig->shapes[2].y1, -1);
			CHECK(fig->shapes[2].x2, 1);
			CHECK(fig->shapes[2].y2, 0);
			CHECK(getShapesCount(fig), 3);

			removeShapeByIndex(fig, 1);
			updateShapes(fig);
			CHECK(fig->shapes[0].type, 'L');
			CHECK(fig->shapes[0].x1, 0);
			CHECK(fig->shapes[0].y1, 0);
			CHECK(fig->shapes[0].x2, 1);
			CHECK(fig->shapes[0].y2, 1);

			CHECK(fig->shapes[1].type, 'C');
			CHECK(fig->shapes[1].x1, -1);
			CHECK(fig->shapes[1].y1, -1);
			CHECK(fig->shapes[1].x2, 1);
			CHECK(fig->shapes[1].y2, 0);
			CHECK(getShapesCount(fig), 2);

			removeShapeByIndex(fig, 1);
			updateShapes(fig);
			CHECK(fig->shapes[0].type, 'L');
			CHECK(fig->shapes[0].x1, 0);
			CHECK(fig->shapes[0].y1, 0);
			CHECK(fig->shapes[0].x2, 1);
			CHECK(fig->shapes[0].y2, 1);

			CHECK(getShapesCount(fig), 1);

			cleanFigure(fig);
			CHECK(getPointsCount(fig), 0);
			CHECK(getShapesCount(fig), 0);
			gShape sh11 = { 'L', 0, 0, 1, 1 };
			gShape sh22 = { 'C', 0 ,0, 1, 0 };
			addShapeToFigure(fig, sh11);
			addShapeToFigure(fig, sh22);
			updateShapes(fig);
			CHECK(fig->shapes[0].type, 'L');
			CHECK(fig->shapes[0].x1, 0);
			CHECK(fig->shapes[0].y1, 0);
			CHECK(fig->shapes[0].x2, 1);
			CHECK(fig->shapes[0].y2, 1);
			CHECK(fig->shapes[1].type, 'C');
			CHECK(fig->shapes[1].x1, 0);
			CHECK(fig->shapes[1].y1, 0);
			CHECK(fig->shapes[1].x2, 1);
			CHECK(fig->shapes[1].y2, 0);
			CHECK(getShapesCount(fig), 2);

			deleteFigure(fig);
			fig = addFigure();
			gShape sh111 = { 'L', 0, 0, 1, 1 };
			gShape sh222 = { 'L', 1, 0, 0, 1 };
			gShape sh333 = { 'L', 0, -1, -1, 0 };
			addShapeToFigure(fig, sh111);
			addShapeToFigure(fig, sh222);
			CHECK(fig->upperleft.x, 0.5);
			CHECK(fig->upperleft.y, 0.5);
			CHECK(fig->lowerright.x, 0.5);
			CHECK(fig->lowerright.y, 0.5);
			addShapeToFigure(fig, sh333);
			CHECK(fig->upperleft.x, -0.5);
			CHECK(fig->upperleft.y, 0.5);
			CHECK(fig->lowerright.x, 0.5);
			CHECK(fig->lowerright.y, -0.5);
		}


	};
}