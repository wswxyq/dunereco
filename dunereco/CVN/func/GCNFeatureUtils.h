////////////////////////////////////////////////////////////////////////
/// \file    GCNFeatureUtils.h
/// \brief   Utilities for calculating feature values for the GCN
/// \author  Leigh Whitehead - leigh.howard.whitehead@cern.ch
////////////////////////////////////////////////////////////////////////

#ifndef GCN_FEATURE_UTILS_H
#define GCN_FEATURE_UTILS_H

#include <vector>
#include <string>
#include <map>

#include "art/Framework/Principal/Event.h"
#include "lardataobj/RecoBase/SpacePoint.h"

#include "dune/CVN/func/GCNGraph.h"
#include "dune/CVN/func/PixelMap.h"

namespace cvn
{

  /// Class containing some utility functions for all things CVN
  class GCNFeatureUtils
  {
  public:
    GCNFeatureUtils();
    ~GCNFeatureUtils();

    /// Get the number of neighbours within rangeCut cm of this space point
    const unsigned int GetSpacePointNeighbours(const recob::SpacePoint &sp, art::Event const &evt, const float rangeCut, const std::string &spLabel) const;
    const unsigned int GetSpacePointNeighbours(const recob::SpacePoint &sp, art::Event const &evt, const float rangeCut, const std::vector<art::Ptr<recob::SpacePoint>> &sps) const;
    /// Get a map of the number of neighbours for each space point ID. Using this function is much less wasteful
    /// than repeated calls to the above function
    const std::map<int,unsigned int> GetAllNeighbours(art::Event const &evt, const float rangeCut, const std::string &spLabel) const;
    const std::map<int,unsigned int> GetAllNeighbours(art::Event const &evt, const float rangeCut, const std::vector<art::Ptr<recob::SpacePoint>> &sps) const;
    /// Use the association between space points and hits to return a charge
    const std::map<unsigned int, float> GetSpacePointChargeMap(art::Event const &evt, const std::string &spLabel) const;
    /// Get the true G4 ID for each spacepoint
    const std::map<unsigned int, unsigned int> GetTrueG4ID(art::Event const& evt, const std::string &spLabel) const;

    /// Convert a pixel map into three 2D GCNGraph objects
    std::vector<cvn::GCNGraph> ExtractGraphsFromPixelMap(const cvn::PixelMap &pm) const;
    /// Get the neighbours map <graph node, neighbours> for the three 2D graph in 2 box (npixel+1) around the pixel
    const std::map<unsigned int,unsigned int> Get2DGraphNeighbourMap(const cvn::GCNGraph &g, const unsigned int npixel) const;

  private:

  };

}

#endif  // GCN_FEATURE_UTILS_H
