#ifndef PARAMETER_H_
#define PARAMETER_H_

#include "Parameterization.h"
#include "ParamPatch.h"

#include <vector>
#include <string>
#include <boost/shared_ptr.hpp>

#include <hj_3rd/zjucad/matrix/matrix.h>

class MeshModel;
class LinearSolver;
class CMeshSparseMatrix;

namespace PARAM
{
    class ChartCreator;

    class Parameter
    {
    public:
        Parameter(boost::shared_ptr<MeshModel> _p_mesh);
        ~Parameter();

		void OptimizeAmbiguityPatch();

        bool ComputeParamCoord();

    public:
        //! IO
        bool LoadPatchFile(const std::string& file_name);

		int GetFaceChartID(int fid) const { return m_face_chart_array[fid]; }
        int GetVertexChartID(int vid) const { return m_vert_chart_array[vid];}
		ParamCoord GetVertexParamCoord(int vid)  const { return m_vert_param_coord_array[vid]; }

		std::vector<ParamCoord> GetFaceVertParamCoord(int fid) const ;


		const std::vector<int>& GetVertexChartArray() const { return m_vert_chart_array; }
		const std::vector<ParamCoord>& GetVertexParamCoordArray() const { return m_vert_param_coord_array; }

		boost::shared_ptr<MeshModel> GetMeshModel() const { return p_mesh; }
		boost::shared_ptr<ChartCreator> GetChartCreator() const { return p_chart_creator; }

        //! for debug
		const std::vector<int>& GetOutRangeVertArray() const { return m_out_range_vert_array; }
		const std::vector<int>& GetUnSetFaceArray() const { return m_unset_layout_face_array; }	
		const std::vector<int>& GetFlipedFaceArray() const { return m_fliped_face_array; }
		const std::vector<int>& GetVertexPatchArray() const { return m_vert_patch_array; }
		const std::vector<int>& GetFacePatchArray() const {return m_face_patch_array; }
	private:
		int SetVariIndexMapping(std::vector<int>& vari_index_mapping);
		void SetBoundaryVertexParamValue(LinearSolver* p_linear_solver = NULL);
        
		void SolveParameter(const CMeshSparseMatrix& lap_mat);

		//! after each iterator, we need reassign vertices's chart  
		void AdjustPatchBoundary();

		void VertexRelalaxation();

		void SetInitVertChartLayout();
		void SetInitFaceChartLayout();
		
	  
		void GetOutRangeVertices(std::vector<int>& out_range_vert_array) const;
		bool FindValidChartForOutRangeVertex(int our_range_vert, int max_ringe_num = 5);
		double ComputeOutRangeError4Square(ParamCoord param_coord) const;		
		double ComputeOutRangeError4TriangleChart(ParamCoord param_coord, int chart_id);

		//! get the length of a mesh path
		double ComputeMeshPathLength(const std::vector<int>& mesh_path, int start_idx, int end_idx) const;

		//! get a conner's index in a patch/chart
		int GetConnerIndexInPatch(int conner_id, int patch_id);

		//! reset face chart layout
		void ResetFaceChartLayout();

		//! set mesh texture 
		void SetMeshFaceTextureCoord();

		//! set each chart's vertices 
		void SetChartVerticesArray();

		//! find the corresponding surface position on chart with the chart parameter coordinate 
		bool FindCorrespondingInChart(const ChartParamCoord& chart_param_coord, 
			int chart_id, SurfaceCoord& surface_coord) const;

		void CheckFlipedTriangle();

		//! check two charts is ambiguity(have more than one common edges)? 
		bool IsAmbiguityChartPair(int chart_id_1, int chart_id_2) const;		

		bool IsConnerVertex(int vert_vid) const;

		bool GetConnerParamCoord(int chart_id, int conner_idx, ParamCoord& conner_pc) const;

	private:
		/// Conner Relocating
		void ConnerRelocating();
	    void ComputeConnerVertexNewParamCoord(int conner_vid, ParamCoord& new_pc) const;

		void FixAdjustedVertex(bool with_conner = false);
		bool FixAdjustedVertex(int vid);

	private:
		//! LocalStiffening;
		void LocalStiffening();

		void ComputeFaceSignFuncValue(std::vector<int>& face_sign_func_value) ;//const;
		void ComputeFaceLocalDistortion(const std::vector<int>& face_sign_func_value, std::vector<double>& face_distortion) const;
		void UpdateStiffeningWeight(const std::vector<double>& face_distortion);

		void SetLapMatrixWithStiffeningWeight(CMeshSparseMatrix& stiffen_lap_mat);
		void SetMeanValueLapMatrixWithStiffeningWeight(CMeshSparseMatrix& stiffen_lap_mat);
		

		int SignFunc(double value) const
		{
			if(fabs(value) < LARGE_ZERO_EPSILON) return 0;
			if(value > 0) return 1;
			else return -1;
		}

	public:

		zjucad::matrix::matrix<double> GetTransMatrix(int from_vid, int to_vid, int from_chart_id, int to_chart_id) const;

// 		void TransParamCoordBetweenCharts(int from_chart_id, int to_chart_id, 
// 			const ParamCoord& from_param_coord, ParamCoord& to_param_coord) const;
		void TransParamCoordBetweenCharts(int from_chart_id, int to_chart_id, int vid, 
			const ParamCoord& from_param_coord, ParamCoord& to_param_coord) const;
		//! for one face's three vertices, they may be in different chart, and we need transite them to same chart.
		//! so there are several choose for the common chart, and our standart is the best triangle shape in parameter domain. 
		int FindBestChartIDForTriShape(int fid) const;

		//! find the corresponding surface position with the chart paramerter coordinate
		bool FindCorrespondingOnSurface(const ChartParamCoord& chart_param_coord,SurfaceCoord& surface_coord) const;

		void ComputeDistortion();
	private:
		boost::shared_ptr<MeshModel> p_mesh;
		boost::shared_ptr<ChartCreator> p_chart_creator;

		std::vector<int> m_vert_chart_array; //! each vertex's chart
		std::vector<int> m_face_chart_array; //! each face's chart

		std::vector<ParamCoord> m_vert_param_coord_array; //! each vertex's parameter coordinate
		std::vector< std::vector<int> > m_chart_vertices_array; //! 

		std::vector<int> m_fixed_conner_array;

		//! for debug
		std::vector<int> m_out_range_vert_array;
		std::vector<int> m_unset_layout_face_array;  
		std::vector<int> m_fliped_face_array;

		std::vector<int> m_vert_patch_array;
		std::vector<int> m_face_patch_array;

		std::vector<double> m_stiffen_weight;

		std::vector<bool> m_flippd_face;
    };
} 

#endif //PARAMETER_H_
