#include <glut.h>
#include "imageloader.h"
#include "texturemodel.h"
#include "model.h"
#include <math.h>

namespace program {
	Model name;
	TextureModel horizontalBox, verticalBox, sky, skyTop, table, ground, floor, horizontalWall, verticalWall, horizontalTulanh, verticalTuLanh, board, barN, barT;
	Vector3 sky_t, skyTop_t, ground_t, horizontalWall_t, horizontalBox_t1, horizontalBox_t2,verticalBox_t1,
		verticalWall_t, horizontalTuLanh_t,verticalTuLanh_t, table_t, board_t, floor_t;
	float lx = 0.0f, lz = 0.0f;
	float x = 0.0f, z = 0.0f;
	float angle = 0;
	float speed = 0.2f;
	float heightAngle = 1;
	float height_view = -1;

	void draw(TextureModel* m, Vector3 t) {
		glPushMatrix();
		glTranslatef(t.x, t.y, t.z);
		m->draw();
		glPopMatrix();
	}
	void makeSky() {
		sky.clear();
		sky.setTextureFromBMP("data/redsky.bmp");
		sky.addVertex(point3(-100, -100, -100));//0
		sky.addVertex(point3(100, -100, -100));//1
		sky.addVertex(point3(-100, 100, -100));//2
		sky.addVertex(point3(100, 100, -100));//3
		sky.addVertex(point3(-100, -100, 100));//4
		sky.addVertex(point3(100, -100, 100));//5
		sky.addVertex(point3(-100, 100, 100));//6
		sky.addVertex(point3(100, 100, 100));//7
		sky.addQuad(quadIndex(2, 3, 1, 0, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0)));
		sky.addQuad(quadIndex(6, 7, 5, 4, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0)));
		sky.addQuad(quadIndex(2, 6, 4, 0, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0)));
		sky.addQuad(quadIndex(3, 7, 5, 1, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0)));

		sky_t = point3(0, 0, 0);
	}
	void makeSkyTop() {
		skyTop.clear();
		skyTop.setTextureFromBMP("data/redsky.bmp");
		skyTop.addVertex(point3(-100, 100, -100));
		skyTop.addVertex(point3(100, 100, -100));
		skyTop.addVertex(point3(100, 100, 100));
		skyTop.addVertex(point3(-100, 100, 100));
		skyTop.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0)));

		skyTop_t = point3(0, 0, 0);
	}
	void makeGround() {
		ground.clear();
		ground.setTextureFromBMP("data/roof1.bmp");
		ground.addVertex(point3(-100, -1.5, 100));
		ground.addVertex(point3(-100, -1.5, -100));
		ground.addVertex(point3(100, -1.5, -100));
		ground.addVertex(point3(100, -1.5, 100));
		ground.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 200), texCoord2(200, 200), texCoord2(200, 0), texCoord2(0, 0)));

		ground_t = point3(0, 0, 0);
	}
	void makeFloor() {
		floor.clear();
		floor.setTextureFromBMP("data/floor2.bmp");
		floor.addVertex(point3(-4, -1.499, 4));
		floor.addVertex(point3(-4, -1.499, -4));
		floor.addVertex(point3(4, -1.499, -4));
		floor.addVertex(point3(4, -1.499, 4));
		floor.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 20), texCoord2(20, 20), texCoord2(20, 0), texCoord2(0, 0)));

		floor_t = point3(-0.99, 0, -2.1);
	}
	void makeHorizontalWall() {
		horizontalWall.clear();
		horizontalWall.setTextureFromBMP("data/wall01.bmp");
		horizontalWall.addVertex(point3(-4, 1, 4));
		horizontalWall.addVertex(point3(4, 1, 4));
		horizontalWall.addVertex(point3(4, -1.5, 4));
		horizontalWall.addVertex(point3(-4, -1.5, 4));
		horizontalWall.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 2), texCoord2(4, 2), texCoord2(4, 0), texCoord2(0, 0)));

		horizontalWall_t = point3(-0.99, 0, -10.1);
	}
	void makeVerticalWall() {
		verticalWall.clear();
		verticalWall.setTextureFromBMP("data/wall01.bmp");
		verticalWall.addVertex(point3(4, 1, 4));
		verticalWall.addVertex(point3(4, 1, -4));
		verticalWall.addVertex(point3(4, -1.5, -4));
		verticalWall.addVertex(point3(4, -1.5, 4));
		verticalWall.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 2), texCoord2(2, 2), texCoord2(2, 0), texCoord2(0, 0)));

		verticalWall_t = point3(-0.99, 0, -2.1);
	}
	void makeHorizontalTulanh() {
		horizontalTulanh.clear();
		horizontalTulanh.setTextureFromBMP("data/tulanh2.bmp");
		horizontalTulanh.addVertex(point3(-4, 0, 1));// 0
		horizontalTulanh.addVertex(point3(0, 0, 1));// 1
		horizontalTulanh.addVertex(point3(0, -1.5, 1));// 2
		horizontalTulanh.addVertex(point3(-4, -1.5, 1));// 3
		horizontalTulanh.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 4), texCoord2(4, 4), texCoord2(4, 0), texCoord2(0, 0)));
		horizontalTuLanh_t = point3(2, 0, -5.99);
	}
	void makeVerticalTulanh() {
		verticalTuLanh.clear();
		verticalTuLanh.setTextureFromBMP("data/tulanh3.bmp");
		verticalTuLanh.addVertex(point3(1, 0, -4));// 0
		verticalTuLanh.addVertex(point3(1, 0, 0));// 1
		verticalTuLanh.addVertex(point3(1, -1.5, 0));// 2
		verticalTuLanh.addVertex(point3(1, -1.5, -4));// 3
		verticalTuLanh.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 8), texCoord2(8, 8), texCoord2(8, 0), texCoord2(0, 0)));
		verticalTuLanh_t = point3(0.99, 0, -1);
	}
	void makeHorizontalBox() {
		horizontalBox.clear();
		horizontalBox.addVertex(point3(-2, 0, 1)); // 0
		horizontalBox.addVertex(point3(0, 0, 1)); // 1
		horizontalBox.addVertex(point3(0, -1.5, 1)); // 2
		horizontalBox.addVertex(point3(-2, -1.5, 1)); // 3
		horizontalBox.addVertex(point3(-2, 0, 0)); // 4
		horizontalBox.addVertex(point3(0, 0, 0)); // 5
		horizontalBox.addVertex(point3(0, -1.5, 0)); // 6
		horizontalBox.addVertex(point3(-2, -1.5, 0)); // 7

		horizontalBox.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0))); // Mặt trước (tuLanhFront)
		horizontalBox.addQuad(quadIndex(4, 5, 6, 7, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0))); // Mặt sau
		horizontalBox.addQuad(quadIndex(0, 4, 7, 3, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0))); // Mặt trái
		horizontalBox.addQuad(quadIndex(1, 5, 6, 2, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0))); // Mặt phải
		horizontalBox.addQuad(quadIndex(0, 1, 5, 4, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0))); // Mặt trên
		horizontalBox.addQuad(quadIndex(3, 2, 6, 7, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0))); // Mặt dưới
	}
	void makeVerticalBox() {
		verticalBox.clear();
		verticalBox.addVertex(point3(-1, 0, 4)); // 0
		verticalBox.addVertex(point3(-1, 0, 0)); // 1
		verticalBox.addVertex(point3(-1, -1.5, 0)); // 2
		verticalBox.addVertex(point3(-1, -1.5, 4)); // 3
		verticalBox.addVertex(point3(0, 0, 4)); // 4
		verticalBox.addVertex(point3(0, 0, 0)); // 5
		verticalBox.addVertex(point3(0, -1.5, 0)); // 6
		verticalBox.addVertex(point3(0, -1.5, 4)); // 7

		// Thêm các mặt của hình hộp chữ nhật
		verticalBox.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0))); // Mặt trước (tuLanhFront)
		verticalBox.addQuad(quadIndex(4, 5, 6, 7, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0))); // Mặt sau
		verticalBox.addQuad(quadIndex(0, 4, 7, 3, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0))); // Mặt trái
		verticalBox.addQuad(quadIndex(1, 5, 6, 2, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0))); // Mặt phải
		verticalBox.addQuad(quadIndex(0, 1, 5, 4, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0))); // Mặt trên
		verticalBox.addQuad(quadIndex(3, 2, 6, 7, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0))); // Mặt dưới

	}
	void makeTable() {
		table.clear();
		table.setTextureFromBMP("data/table.bmp");
		table.addVertex(point3(-1.5, 0, 1)); // 0
		table.addVertex(point3(0, 0, 1)); // 1
		table.addVertex(point3(0, -0.7, 1)); // 2
		table.addVertex(point3(-1.5, -0.7, 1)); // 3
		table.addVertex(point3(-1.5, 0, 0)); // 4
		table.addVertex(point3(0, 0, 0)); // 5
		table.addVertex(point3(0, -0.7, 0)); // 6
		table.addVertex(point3(-1.5, -0.7, 0)); // 7

		table.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0))); // Mặt trước (tuLanhFront)
		table.addQuad(quadIndex(4, 5, 6, 7, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0))); // Mặt sau
		table.addQuad(quadIndex(0, 4, 7, 3, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0))); // Mặt trái
		table.addQuad(quadIndex(1, 5, 6, 2, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0))); // Mặt phải
		table.addQuad(quadIndex(0, 1, 5, 4, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0))); // Mặt trên
		table.addQuad(quadIndex(3, 2, 6, 7, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0))); // Mặt dưới
		table_t = point3(-3, -0.8, -5);
	}
	void makeBoard() {
		board.clear();
		board.setTextureFromBMP("data/board.bmp");
		board.addVertex(point3(-1, 0, 1));
		board.addVertex(point3(1, 0, 1));
		board.addVertex(point3(1, -1.5, 1));
		board.addVertex(point3(-1, -1.5, 1));
		board.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0)));

		board_t = point3(-3.5, 0.5, -6.999);
	}
	void resize(int width, int height) {
		if (height == 0) height = 1;
		const float ar = (float)width / (float)height;
		glViewport(0, 0, width, height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f, ar, 0.1f, 1000.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	void renderScene(void) {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glLoadIdentity();

		gluLookAt(x, 0, z,
			x + lx, height_view, z + lz,
			0.0f, 2.0f, 0.0f);

		glEnable(GL_TEXTURE_2D);
		horizontalBox_t1 = point3(0, 0, -6);
		horizontalBox_t2 = point3(2, 0, -6);
		
		verticalBox_t1 = point3(3, 0, -5);
		draw(&sky, sky_t);
		draw(&skyTop, skyTop_t);
		for (int x1 = -5; x1 < 5; x1++) {
			for (int z1 = -5; z1 < 5; z1++) {
				Vector3 ground_t1;
				ground_t1.x = x1;
				ground_t1.z = z1;
				ground_t1.y = 0;

				draw(&ground, ground_t1);
			}
		}
		draw(&floor, floor_t);
		draw(&horizontalWall, horizontalWall_t);
		draw(&verticalWall, verticalWall_t);
		draw(&horizontalBox, horizontalBox_t1);
		draw(&horizontalBox, horizontalBox_t2);
		draw(&verticalBox, verticalBox_t1);
		draw(&table, table_t);
		draw(&board, board_t);
		draw(&horizontalTulanh, horizontalTuLanh_t);
		draw(&verticalTuLanh, verticalTuLanh_t);
		glutSwapBuffers();
		glFlush();
	}
	void processKeys(unsigned char key, int xx, int yy) {
		switch (key) {
		case '>':
			speed += 0.1;
			break;
		case '<':
			speed -= 0.1;
			break;
		case 'w':
			if (heightAngle < PI / 2) {
				heightAngle += 0.1;
				height_view = sin(heightAngle) - 1;
			}
			break;
		case 's':
			if (heightAngle > (-PI / 2)) {
				heightAngle -= 0.1;
				height_view = sin(heightAngle) - 1;
			}
			break;
		case 'a':
			angle -= 0.02f;
			lx = cos(angle);
			lz = sin(angle);
			break;
		case 'd':
			angle += 0.02f;
			lx = cos(angle);
			lz = sin(angle);
			break;
		default:
			break;
		}
		glutPostRedisplay();
	}
	void processSpecialKeys(int key, int xx, int yy) {

		float fraction = speed;

		switch (key) {
		case GLUT_KEY_LEFT:
			x += lz * fraction;
			z -= lx * fraction;
			break;
		case GLUT_KEY_RIGHT:
			x -= lz * fraction;
			z += lx * fraction;
			break;
		case GLUT_KEY_UP:
			x += lx * fraction;
			z += lz * fraction;
			break;
		case GLUT_KEY_DOWN:
			x -= lx * fraction;
			z -= lz * fraction;
			break;
		}glutPostRedisplay();
	}

	void init() {
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		lx = cos(angle);
		lz = sin(angle);

		makeSky();
		makeSkyTop();
		makeGround();
		makeFloor();
		makeHorizontalTulanh();
		makeVerticalTulanh();
		makeHorizontalBox();
		makeVerticalBox();
		makeVerticalWall();
		makeHorizontalWall();
		makeTable();
		makeBoard();
	}
}
int main(int argc, char** argv) {
	glutInitDisplayMode(GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1200, 800);
	glutCreateWindow("Cua Hang Tap Hoa");
	glEnable(GL_DEPTH_TEST);

	glutReshapeFunc(program::resize);
	glutKeyboardFunc(program::processKeys);
	glutSpecialFunc(program::processSpecialKeys);
	glutDisplayFunc(program::renderScene);
	program::init();

	glutMainLoop();
	return 0;
}