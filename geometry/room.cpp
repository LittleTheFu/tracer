#include "room.h"
#include "materialManager.h"
#include "tri.h"

Room::Room()
{
    init();
    refine();
    refine();
    refine();
    refine();
    refine();
    refine();
    refine();
    refine();
}

std::vector<Geometry *> Room::getTris() const
{
    return m_tris;
}

//a tri follows anti clockwise rule
void Room::init()
{
    //HALF_WIDTH
    float hw = 100;
    float depth = 400;
    //front left
    TriVertex a_fl(hw, hw, depth);
    TriVertex b_fl(hw, -hw, depth);
    TriVertex c_fl(-hw, hw, depth);

    Tri *tri_fl = new Tri(a_fl, b_fl, c_fl, Vector3(0,0,0), MaterialManager::getInstance()->get(MATERIAL_TYPE::M_RED));

    m_tris.push_back(tri_fl);

    //front right
    TriVertex a_fr(-hw, -hw, depth);
    TriVertex b_fr(-hw, hw, depth);
    TriVertex c_fr(hw, -hw, depth);

    Tri *tri_fr = new Tri(a_fr, b_fr, c_fr, Vector3(0,0,0), MaterialManager::getInstance()->get(MATERIAL_TYPE::M_RED));
    m_tris.push_back(tri_fr);

    //left near
    TriVertex a_ln(hw, -hw, -depth);
    TriVertex b_ln(hw, -hw, depth);
    TriVertex c_ln(hw, hw, -depth);

    Tri *tri_ln = new Tri(a_ln, b_ln, c_ln, Vector3(0,0,0), MaterialManager::getInstance()->get(MATERIAL_TYPE::M_PURPLE));
    m_tris.push_back(tri_ln);

    //left far
    TriVertex a_lf(hw, hw, depth);
    TriVertex b_lf(hw, hw, -depth);
    TriVertex c_lf(hw, -hw, depth);

    Tri *tri_lf = new Tri(a_lf, b_lf, c_lf, Vector3(0,0,0), MaterialManager::getInstance()->get(MATERIAL_TYPE::M_PURPLE));
    m_tris.push_back(tri_lf);

    //right near
    TriVertex a_rn(-hw, -hw, -depth);
    TriVertex b_rn(-hw, hw, -depth);
    TriVertex c_rn(-hw, -hw, depth);

    Tri *tri_rn = new Tri(a_rn, b_rn, c_rn, Vector3(0,0,0), MaterialManager::getInstance()->get(MATERIAL_TYPE::M_AQUA));
    m_tris.push_back(tri_rn);

    //right far
    TriVertex a_rf(-hw, hw, depth);
    TriVertex b_rf(-hw, -hw, depth);
    TriVertex c_rf(-hw, hw, -depth);

    Tri *tri_rf = new Tri(a_rf, b_rf, c_rf, Vector3(0,0,0), MaterialManager::getInstance()->get(MATERIAL_TYPE::M_AQUA));
    m_tris.push_back(tri_rf);

    //bottom near
    TriVertex a_bn(hw, -hw, -depth);
    TriVertex b_bn(-hw, -hw, -depth);
    TriVertex c_bn(hw, -hw, depth);

    Tri *tri_bn = new Tri(a_bn, b_bn, c_bn, Vector3(0,0,0), MaterialManager::getInstance()->get(MATERIAL_TYPE::M_YELLOW));
    m_tris.push_back(tri_bn);

    //bottom far
    TriVertex a_bf(-hw, -hw, depth);
    TriVertex b_bf(hw, -hw, depth);
    TriVertex c_bf(-hw, -hw, -depth);

    Tri *tri_bf = new Tri(a_bf, b_bf, c_bf, Vector3(0,0,0), MaterialManager::getInstance()->get(MATERIAL_TYPE::M_YELLOW));
    m_tris.push_back(tri_bf);

     //top near
    TriVertex a_tn(hw, hw, -depth);
    TriVertex b_tn(hw, hw, depth);
    TriVertex c_tn(-hw, hw, -depth);

    Tri *tri_tn = new Tri(a_tn, b_tn, c_tn, Vector3(0,0,0), MaterialManager::getInstance()->get(MATERIAL_TYPE::M_BLUE));
    m_tris.push_back(tri_tn);

    //top far
    TriVertex a_tf(-hw, hw, depth);
    TriVertex b_tf(-hw, hw, -depth);
    TriVertex c_tf(hw, hw, depth);

    Tri *tri_tf = new Tri(a_tf, b_tf, c_tf, Vector3(0,0,0), MaterialManager::getInstance()->get(MATERIAL_TYPE::M_BLUE));
    m_tris.push_back(tri_tf);

     //back left
    TriVertex a_bl(hw, hw, -depth);
    TriVertex b_bl(-hw, hw, -depth);
    TriVertex c_bl(hw, -hw, -depth);
    
    Tri *tri_bl = new Tri(a_bl, b_bl, c_bl, Vector3(0,0,0), MaterialManager::getInstance()->get(MATERIAL_TYPE::M_WHITE));
    m_tris.push_back(tri_bl);

    //back right
    TriVertex a_br(-hw, -hw, -depth);
    TriVertex b_br(hw, -hw, -depth);
    TriVertex c_br(-hw, hw, -depth);

    Tri *tri_br = new Tri(a_br, b_br, c_br, Vector3(0,0,0), MaterialManager::getInstance()->get(MATERIAL_TYPE::M_WHITE));
    m_tris.push_back(tri_br);
}

void Room::refine()
{
    std::vector<Geometry*> v;

    for(auto it = m_tris.begin(); it != m_tris.end(); it++)
    {
        Tri* a = new Tri();
        Tri *b = new Tri();
        Tri *c = new Tri();

        ((Tri*)(*it))->getSplitChildren(a,b,c);

        v.push_back(a);
        v.push_back(b);
        v.push_back(c);

        delete (*it);
    }

    m_tris.clear();
    m_tris = v;
}
