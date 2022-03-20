

#pragma once

namespace _3DLab {
	// A struct have three float points represent position
	struct Point3D {
	//public:
		Point3D() {}
		Point3D(float x, float y, float z)
			: x(x), y(y), z(z) {}
		virtual ~Point3D() {}

		float x = 0.f;
		float y = 0.f;
		float z = 0.f;
	};

	struct Vertex {
	//public:
		Vertex() { }
		Vertex(float x, float y, float z)
			: m_position(Point3D{ x, y, z }) {}
		virtual ~Vertex() { }

		Point3D m_position;
	};

	struct Polygon {
	//public:
		Polygon() { }
		Polygon(int numberOfVertices);
		virtual ~Polygon();

		//다각형(면)을 구성하는 정점들의 리스트이다.
		int m_numberOfVertices = 0;
		Vertex* m_ptrToVertices = nullptr;
		void SetVertex(int indexNumber, Vertex vertex);
	};


	class Mesh {
	public:
		Mesh() {}
		Mesh(int numberOfPolygons);
		virtual ~Mesh();

	private:
		// 인스턴싱을 위하여 메쉬는 게임 객체들에 공유될 수 있다
		// 다음 참조값은 메쉬가 공유되는 게임 객체의 개수
		int m_numberOfReferences = 1;

	public:
		// 메쉬가 게임 객체에 공유될 때마다 참조값을 1씩 증가
		void AddRef() {
			++m_numberOfReferences;
		}
		// 메쉬를 공유하는 게임 객체가 소멸될 때마다 참조값을 1씩 감소
		// 참조값이 0이되면 메쉬를 소멸시킨다
		// 이부분 테스트해보기
		void Release() {
			--m_numberOfReferences;
			if (m_numberOfReferences <= 0) {
				delete this;
			}
		}

	private:
		int m_numberOfPolygons = 0;
		// pointing to array of polygons
		Polygon** m_ptrToPolygons = nullptr;

	public:
		void SetPolygon(int indexNumber, Polygon* ptrToPolygon);

		virtual void Render(HDC hDCFrameBuffer);
	};

	class CubeMesh : public Mesh {
	public:
		CubeMesh(float width = 4.f, float height = 4.f, float depth = 4.f);
		virtual ~CubeMesh();
	};

}