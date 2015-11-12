#include "FibersMaterial.h"

template <>
	InputParameters validParams<FibersMaterial>() {
  InputParameters params = validParams<Material>();
  return params;
}

FibersMaterial::FibersMaterial(const InputParameters & parameters) :
    Material(parameters),
    _fiberDirection(declareProperty<RealVectorValue>("fiberDirection")),
    _sheetDirection(declareProperty<RealVectorValue>("sheetDirection")),
    _normalDirection(declareProperty<RealVectorValue>("normalDirection")),
    _fXf(declareProperty<RealTensorValue>("fiberOuterFiber")),
    _sXs(declareProperty<RealTensorValue>("sheetOuterSheet")),
    _fXs(declareProperty<RealTensorValue>("fiberOuterSheet")),
    _nXn(declareProperty<RealTensorValue>("normalOuterNormal")),
    _rotationTensor(declareProperty<RealTensorValue>("rotationTensor"))
    {}


void FibersMaterial::computeQpTensorProperties()
{
	for (int i=0; i<3; ++i)
		for (int j=0; j<3; ++j)
		{
			_fXf[_qp](i,j)=_fiberDirection[_qp](i)*_fiberDirection[_qp](j);
			_sXs[_qp](i,j)=_sheetDirection[_qp](i)*_sheetDirection[_qp](j);
			_fXs[_qp](i,j)=_fiberDirection[_qp](i)*_sheetDirection[_qp](j);
      _nXn[_qp](i,j)=_normalDirection[_qp](i)*_normalDirection[_qp](j);
		}


		// Here we symmetrize _fXs, maybe this operation is not needed or dangerous

		_fXs[_qp]=0.5*( _fXs[_qp] + _fXs[_qp].transpose() );


  for (int i = 0; i < 3; ++i)
  {
    _rotationTensor[_qp](i, 0) = _fiberDirection[_qp](i);
    _rotationTensor[_qp](i, 1) = _sheetDirection[_qp](i);
    _rotationTensor[_qp](i, 2) = _normalDirection[_qp](i);
  }

// This part checks that _RotationTensor is orthonormal
 RealTensorValue OP = _rotationTensor[_qp].transpose() * _rotationTensor[_qp];


  for (int i = 0; i < 3; ++i)
  {
    for (int j = 0; j < 3; ++j)
    {
      if (i == j)
      {
        if (fabs(OP(i, j) - 1.0) > 1e-10)
        {
          std::cout<<OP<<std::endl;
          exit(1);
        }
      }
      else
      {
        if (fabs(OP(i, j)) > 1e-10)
        {
          exit(1);
        }
      }
    }
  }

}