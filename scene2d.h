#pragma once

#include "rendering/rendering.h"
#include "rasterization/bitmap.h"
#include "core2d/model2d.h"
#include "core2d/camera2d.h"

class Scene2d
{
public:
	Scene2d(
		const Core2d::Camera2d& camera,
		const int pixelSize = 1,
		const Rasterization::Color bgColor = Rasterization::colorBlack
	);
	~Scene2d();

	Core2d::Camera2d camera() const;

	void addModel(
		const Core2d::Model2d& model,
		const Rasterization::Color &color,
		const bool isSelected = false);

	void setAxesModel(const int modelInd);

	void run();

private:
	void setTitle(const float frameTime);
	void render();
	void handleTransform(const float frameTime);

	GLFWwindow *m_window = nullptr;
	Rendering::FramebufferData m_bufData;

	int m_width = 0;
	int m_height = 0;
	int m_pixelSize = 1;

	Coord2d m_cursorPos;
	bool m_isPanning = false;
	bool m_isTranslating = false;

	Rasterization::Color m_bgColor;
	std::vector<Rasterization::Color> m_modelColors;

	std::vector<Core2d::Model2d> m_models;
	Core2d::Camera2d m_camera;

	HomogCoords2d m_verticesInProgress;
	AdjacencyMat m_adjacencyInProgress;

	int m_selectedModelInd = -1;
	Rasterization::Color m_selectionColor = Rasterization::colorWhite;

	int m_axesModelInd = -1;
	Rasterization::Color m_axesSelectionColor = Rasterization::colorGreen;

	float m_zoomFactor = 0.1f;

	float m_rotationParam = 0.03f;
	float m_scaleParam = 0.01f;

	Coord2d m_axesCenter = Coord2d(0.0f, 0.0f);
	float m_axesAngle = 0.0f;

	static void resizeCallback(
		GLFWwindow* window,
		const int newWidth, const int newHeight);

	static void cursorPosCallback(
		GLFWwindow* window,
		const double newX, const double newY);

	static void scrollCallback(
		GLFWwindow* window,
		const double dx, const double dy);

	static void mouseButtonCallback(
		GLFWwindow* window,
		const int button, const int action, const int mods);

	static void keyCallback(
		GLFWwindow* window,
		const int key, const int scancode, const int action, const int mods);
};
