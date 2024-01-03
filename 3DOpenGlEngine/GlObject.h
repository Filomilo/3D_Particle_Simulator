/**
 * @file glObject.h
 * @author Filip Borowiec (fborowiec@wp.pl)
 * @brief file conaitng gl object class
 * @version 0.1
 * @date 2024-01-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once
#include "Material.h"
#include "Renderable.h"
#include "Transformable.h"
#include "VAO.h"
/**
 * @brief gl object class for magnign object drawable by opengl
 * 
 */
class GlObject :
	public Renderable,
	public Transformable
{
protected:

	/**
	 * @brief vertex attrivute array for object
	 * 
	 */
	std::shared_ptr<VAO> vao;
	/**
	 * @brief vertex buffer for obejct
	 * 
	 */
	std::shared_ptr<VBO> vbo;
	/**
	 * @brief material including shader for rendering object
	 */
	std::shared_ptr<Material> mat;
/**
 * @brief render mode for opengl
 * 
 */
	int renderMode = GL_FILL;
	/**
	 * @brief gl update usage
	 * 
	 */
	long int usage = GL_STATIC_DRAW;
/**
 * @brief Get the Vertex Buffer For Mat object
 * method taht is suupsoe to creat vertex buffer for specifc matetiral
 * 
 * @param mat 
 * @return GLfloat* 
 */
	virtual GLfloat* getVertexBufferForMat(std::shared_ptr<Material> mat) = 0;

/**
 * @brief Get the Vertex Buffer object
 * 
 * method that is supoose to creat vertex buffer for already applied amterial
 * 
 * @return GLfloat* 
 */
	virtual GLfloat* getVertexBuffer() = 0;
/**
 * @brief Get the Vertex Size For Mat object
 * rutune vertex size for spcif material
 * 
 * @param mat 
 * @return int 
 */
	int getVertexSizeForMat(std::shared_ptr<Material> mat)
	{
		return mat->getVertexSizeRequired();
	}
	/**
	 * @brief Get the Vertex Size object
	 * return vertex size for already applied materail
	 * 
	 * @return int 
	 */
	int getVertexSize()
	{
		return getVertexSizeForMat(this->mat);
	}
/**
 * @brief Get the Vertecies Amount object
 * 
 * return amount of verteixes in object
 * 
 * @return int 
 */
	virtual int getVerteciesAmount() = 0;
	/**
	 * @brief Get the Vertex Attrib object
	 * 
	 * return vetex attirubte of sepcified index
	 * 
	 * @param num index of attributr
	 * @param attrib name of attribute
	 * @return std::shared_ptr<Attribute> 
	 */
	virtual std::shared_ptr<Attribute> getVertexAttrib(int num, std::string attrib) = 0;

/**
 * @brief Get the Map Of Attributes object
 * returns map of attribute
 * 
 * @return std::map<std::string, Attribute::Types> 
 */
	std::map<std::string, Attribute::Types> getMapOfAttributes()
	{
		return this->mat->getAttributeMap();
	}
/**
 * @brief Get the List Of Attributes object
 * 
 * retruns list ofa ttribute in order
 * 
 * @return std::list<std::string> 
 */
	std::list<std::string> getListOfAttributes()
	{
		return this->mat->getAttributeList();
	}
/**
 * @brief Get the Size Of Vertex object
 * returns size of vertex
 * 
 * @return int 
 */
	int getSizeOfVertex()
	{
		return this->mat->getVertexSizeRequired();
	}

/**
 * @brief inirilze vertex buffer for object
 * 
 * @param vertexBuffer 
 * @param verteciesAmt 
 * @param vertexSize 
 * @param vbo 
 * @param vao 
 */
	void iniitVboUniversal(GLfloat* vertexBuffer, int verteciesAmt, int vertexSize, std::shared_ptr<VBO>& vbo, std::shared_ptr<VAO>& vao)
	{
		/*
		for (int i = 0; i < verteciesAmt * vertexSize; i++)
		{
			std::cout << vertexBuffer[i] << ",";
			if (i % vertexSize == vertexSize - 1)
				std::cout << std::endl;
		}
		*/
		
		vao->bind();
		vbo = std::make_unique <VBO>(vertexBuffer, this->getVerteciesAmount() * this->getVertexSize() * sizeof(float), usage);
		delete[] vertexBuffer;
	}


/**
 * @brief initlize vretx buffer for specif object
 * 
 */
	void iniitVbo()
	{


		iniitVboUniversal(this->getVertexBuffer(), this->getVerteciesAmount(), this->getVertexSize(), this->vbo,this->vao);

	}
	/**
	 * @brief update vertex buffer unierslly
	 * 
	 * @param vertexBuffer 
	 * @param verteciesAmt 
	 * @param vertexSize 
	 * @param usage 
	 * @param vbo 
	 * @param vao 
	 */
	void updateVboUNiversal(GLfloat* vertexBuffer, int verteciesAmt, int vertexSize,long usage, std::shared_ptr<VBO>& vbo, std::shared_ptr<VAO>& vao)
	{
		vbo->bind();
		vbo->update(vertexBuffer, verteciesAmt * vertexSize * sizeof(float), usage);;
		vbo->unbind();
		delete[] vertexBuffer;
	}
/**
 * @brief updated vertex buffer for specifc object
 * 
 */
	void updateVbo()
	{
		GLfloat* vertexBuffer = this->getVertexBuffer();
	//	std::cout << "u[date vbo" << std::endl;
		updateVboUNiversal(vertexBuffer, this->getVerteciesAmount(), this->getVertexSize(), usage, this->vbo,this->vao);
	}
/**
 * @brief initlize VAo for object
 * 
 */
	void iniitVao()
	{

		int verteciesAmt = this->getVerteciesAmount();
		int vertexSize = this->getVertexSize();

		std::map<std::string, Attribute::Types> attributesMap = mat->getAttributeMap();
		std::list<std::string> attributeList = mat->getAttributeList();

		int i = 0;
		int offset = 0;
		
		for (std::string name : attributeList)
		{
			Attribute::Types type = attributesMap[name];
			this->vao->linkAttrib(vbo, i, type, GL_FLOAT, vertexSize * sizeof(float), offset);
			glEnableVertexAttribArray(i);
			//std::cout << "glEnableVertexAttribArray(" << i << ")\n";
			i++;
			offset += type * sizeof(float);
		}

	}
/**
 * @brief bind all object buffer
 * 
 */
	virtual void bind()
	{
		this->vbo->bind();
		this->vao->bind();
	}
	/**
	 * @brief unbind all object buffers
	 * 
	 */
	virtual void unbind()
	{
		vao->unbind();
		vbo->unbind();
	}
	/**
	 * @brief call to open gl draw call for sepcifc object
	 * 
	 */
	virtual void glDrawCall() = 0;
/**
 * @brief reneeing priced for opengl
 * 
 */
	void renderProc() override
	{
		glPolygonMode(GL_FRONT_AND_BACK, renderMode);
		if (mat != nullptr)
			mat->apply(this->getTransformationMatrix());
		bind();
		glDrawCall();
		unbind();
		mat->unapply();
	}
public:

	friend class PointGroupInstanced;
	/**
	 * @brief Construct a new Gl Object object
	 * 
	 */
	GlObject() : Transformable()
	{
			this->vao = std::make_shared<VAO>() ;
	}


/**
 * @brief Get the render mode object
 * 
 * @return int 
 */
	int get_render_mode() const
	{
		return renderMode;
	}
/**
 * @brief Set the render mode object
 * 
 * @param render_mode 
 */
	void set_render_mode(int render_mode)
	{
		renderMode = render_mode;
	}
	/**
	 * @brief Set the Mat object
	 * 
	 * @param mat 
	 */
	void setMat(std::shared_ptr<Material>  mat)
	{
		this->mat = mat;
	}
	/**
	 * @brief intilizes buffers of objeect
	 * 
	 */
	virtual void initParts()
	{
		iniitVbo();
		iniitVao();
	}
	/**
	 * @brief nitlizes object
	 * 
	 */
	void init()
	{
		initParts();
		unbind();
	}
/**
 * @brief Get the usage object
 * 
 * @return long 
 */
	long get_usage() const
	{
		return usage;
	}
/**
 * @brief Set the usage object
 * 
 * @param usage 
 */
	void set_usage(long usage)
	{
		this->usage = usage;
	}
};

