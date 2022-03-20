

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

		//�ٰ���(��)�� �����ϴ� �������� ����Ʈ�̴�.
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
		// �ν��Ͻ��� ���Ͽ� �޽��� ���� ��ü�鿡 ������ �� �ִ�
		// ���� �������� �޽��� �����Ǵ� ���� ��ü�� ����
		int m_numberOfReferences = 1;

	public:
		// �޽��� ���� ��ü�� ������ ������ �������� 1�� ����
		void AddRef() {
			++m_numberOfReferences;
		}
		// �޽��� �����ϴ� ���� ��ü�� �Ҹ�� ������ �������� 1�� ����
		// �������� 0�̵Ǹ� �޽��� �Ҹ��Ų��
		// �̺κ� �׽�Ʈ�غ���
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