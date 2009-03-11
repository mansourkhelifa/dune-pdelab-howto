#include<dune/grid/io/file/vtk/subsamplingvtkwriter.hh>
#include<dune/pdelab/common/vtkexport.hh>
#include<dune/pdelab/gridfunctionspace/gridfunctionspace.hh>
#include<dune/pdelab/gridfunctionspace/gridfunctionspaceutilities.hh>
#include<dune/pdelab/gridfunctionspace/interpolate.hh>
#include<dune/pdelab/finiteelementmap/q22dfem.hh>
#include"integrateinterpolationerror.hh"

template<typename GV>
void q2interpolationerror (const GV& gv)
{
  typedef typename GV::Grid::ctype D; // domain type
  typedef double R;                   // range type

  Dune::PDELab::Q22DLocalFiniteElementMap<D,R> fem; // Q_2 now !

  typedef Dune::PDELab::GridFunctionSpace<GV,
	Dune::PDELab::Q22DLocalFiniteElementMap<D,R> > GFS;    
  GFS gfs(gv,fem);                    // make grid function space

  typedef typename GFS::template VectorContainer<R>::Type V;
  V x(gfs,0.0);                       // make coefficient vector

  U<GV,R> u(gv);                      // make analytic function object
  Dune::PDELab::interpolate(u,gfs,x); // make x interpolate u

  std::cout.precision(8);
  std::cout << "interpolation error: " 
			<< std::setw(8) << gv.size(0) << " elements " 
			<< std::scientific << integrateinterpolationerror(u,gfs,x,4) << std::endl;
}
