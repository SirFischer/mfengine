#include "Camera.hpp"
#include "Mesh.hpp"
#include "Light.hpp"
#include "Terrain.hpp"
#include "Model.hpp"

namespace mf
{
	class StaticInstancingBatch
	{
	private:
		std::vector<Mesh *>		mMeshes;
		std::vector<glm::mat4>	mTransformMatrices;
		GLuint					mTransformBuffer;
		bool					mFinalized = false;

	public:
								StaticInstancingBatch(Model	*tModel);
								StaticInstancingBatch(Mesh	*tMesh);
								~StaticInstancingBatch();

		void					AddInstance(glm::mat4 tTransform);
		void					Finalize();
		void					Draw(GLenum mode);
	};	
} // namespace mf
