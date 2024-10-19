#include "room.h"
#include "materialManager.h"
#include "tri.h"

Room::Room()
{
    init();
}

std::vector<Geometry *> Room::getTris() const
{
    return m_tris;
}

//a tri follows anti clockwise rule
void Room::init()
{
    //front left
    TriVertex a_fl(60, 60, 350);
    TriVertex b_fl(60, -60, 350);
    TriVertex c_fl(-60, 60, 350);

    Tri *tri_fl = new Tri(a_fl, b_fl, c_fl, Vector3(0,0,0), MaterialManager::getInstance()->get(MATERIAL_TYPE::M_RED));

    m_tris.push_back(tri_fl);

    //front right
    TriVertex a_fr(-60, -60, 350);
    TriVertex b_fr(-60, 60, 350);
    TriVertex c_fr(60, -60, 350);

    Tri *tri_fr = new Tri(a_fr, b_fr, c_fr, Vector3(0,0,0), MaterialManager::getInstance()->get(MATERIAL_TYPE::M_YELLOW));
    m_tris.push_back(tri_fr);

    //left near
    TriVertex a_ln(60, -60, 230);
    TriVertex b_ln(60, -60, 350);
    TriVertex c_ln(60, 60, 230);

    Tri *tri_ln = new Tri(a_ln, b_ln, c_ln, Vector3(0,0,0), MaterialManager::getInstance()->get(MATERIAL_TYPE::M_PURPLE));
    m_tris.push_back(tri_ln);

    //left far
    TriVertex a_lf(60, 60, 350);
    TriVertex b_lf(60, 60, 230);
    TriVertex c_lf(60, -60, 350);

    Tri *tri_lf = new Tri(a_lf, b_lf, c_lf, Vector3(0,0,0), MaterialManager::getInstance()->get(MATERIAL_TYPE::M_YELLOW));
    m_tris.push_back(tri_lf);

    //right near
    TriVertex a_rn(-60, -60, 230);
    TriVertex b_rn(-60, 60, 230);
    TriVertex c_rn(-60, -60, 350);

    Tri *tri_rn = new Tri(a_rn, b_rn, c_rn, Vector3(0,0,0), MaterialManager::getInstance()->get(MATERIAL_TYPE::M_PURPLE));
    m_tris.push_back(tri_rn);

    //right far
    TriVertex a_rf(-60, 60, 350);
    TriVertex b_rf(-60, -60, 350);
    TriVertex c_rf(-60, 60, 230);

    Tri *tri_rf = new Tri(a_rf, b_rf, c_rf, Vector3(0,0,0), MaterialManager::getInstance()->get(MATERIAL_TYPE::M_YELLOW));
    m_tris.push_back(tri_rf);

    //bottom near
    TriVertex a_bn(60, -60, 230);
    TriVertex b_bn(-60, -60, 230);
    TriVertex c_bn(60, -60, 350);

    Tri *tri_bn = new Tri(a_bn, b_bn, c_bn, Vector3(0,0,0), MaterialManager::getInstance()->get(MATERIAL_TYPE::M_AQUA));
    m_tris.push_back(tri_bn);

    //bottom far
    TriVertex a_bf(-60, -60, 350);
    TriVertex b_bf(60, -60, 350);
    TriVertex c_bf(-60, -60, 230);

    Tri *tri_bf = new Tri(a_bf, b_bf, c_bf, Vector3(0,0,0), MaterialManager::getInstance()->get(MATERIAL_TYPE::M_PURPLE));
    m_tris.push_back(tri_bf);

     //top near
    TriVertex a_tn(60, 60, 230);
    TriVertex b_tn(60, 60, 350);
    TriVertex c_tn(-60, 60, 230);

    Tri *tri_tn = new Tri(a_tn, b_tn, c_tn, Vector3(0,0,0), MaterialManager::getInstance()->get(MATERIAL_TYPE::M_AQUA));
    m_tris.push_back(tri_tn);

    //top far
    TriVertex a_tf(-60, 60, 350);
    TriVertex b_tf(-60, 60, 230);
    TriVertex c_tf(60, 60, 350);

    Tri *tri_tf = new Tri(a_tf, b_tf, c_tf, Vector3(0,0,0), MaterialManager::getInstance()->get(MATERIAL_TYPE::M_GREEN));
    m_tris.push_back(tri_tf);




     //back left
    TriVertex a_bl(60, 60, 230);
    TriVertex b_bl(-60, 60, 230);
    TriVertex c_bl(60, -60, 230);
    
    Tri *tri_bl = new Tri(a_bl, b_bl, c_bl, Vector3(0,0,0), MaterialManager::getInstance()->get(MATERIAL_TYPE::M_GLASS));

    m_tris.push_back(tri_bl);

    //back right
    TriVertex a_br(-60, -60, 230);
    TriVertex b_br(60, -60, 230);
    TriVertex c_br(-60, 60, 230);

    Tri *tri_br = new Tri(a_br, b_br, c_br, Vector3(0,0,0), MaterialManager::getInstance()->get(MATERIAL_TYPE::M_GLASS));
    m_tris.push_back(tri_br);
}
