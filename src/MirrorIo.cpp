// mirror_io.cpp ver 1.01

// this file is covered by the General Public License version 2 or later
// please see GPL.html for more details and licensing issues

// copyright Etienne de Foras ( the author )
// mailto: etienne.deforas@gmail.com

#include "Properties.h"

#include "MirrorIo.h"
#include "Mirror.h"

#include "MirrorComment.h"
#include "MirrorWork.h"
#include "MirrorCouderMeasure.h"
#include "MirrorUnmaskedMeasure.h"

#include <sstream>
#include <cassert>

////////////////////////////////////////////////////////////////////////////////
Mirror* MirrorIo::load(string sFile)
{
    Properties p;
    if(p.load(sFile)==false)
        return 0;

    Mirror* pm=new Mirror;
    pm->set_name(p.get("Name"));
    pm->set_diameter(p.get_double("Diameter"));
    pm->set_hole_diameter(p.get_double("HoleDiameter"));
    pm->set_obstruction_size(p.get_double("ObstructionSize"));
    pm->set_edge_mask_width(p.get_double("EdgeMaskWidth"));
    pm->set_focal(p.get_double("Focal"));
    pm->set_conical(p.get_double("Conical"));

    if(p.exist("MovingLight"))
        pm->set_is_slit_moving(p.get_bool("MovingLight"));

    // old format compatibility, will be removed later
    if(p.exist("IsSlitMoving"))
        pm->set_is_slit_moving(p.get_bool("IsSlitMoving"));

    if(p.exist("SmoothCurves"))
        pm->set_smooth_curves(p.get_bool("SmoothCurves"));

    pm->set_hx(p.get_vector_double("Hx"));

    if(p.exist("ShowBothSides"))
        pm->set_show_both_side(p.get_bool("ShowBothSides"));
    else
        pm->set_show_both_side(true);

    if(p.exist("ShowColors"))
        pm->set_show_colors(p.get_bool("ShowColors"));
    else
        pm->set_show_colors(false);

    if(p.exist("DisplayMode"))
        pm->set_display_mode(p.get_int("DisplayMode"));
    else
        pm->set_display_mode(1);

    pm->initialize();

    int iIndex=0;
    while(true)
    {
        stringstream ss;
        ss << iIndex;
        string sIndex=ss.str();
        iIndex++;

        // lit la mesure iIndex
        if(!p.exist(sIndex+".Type"))
            break;

        string sType=p.get(sIndex+".Type");

        if(sType=="MirrorComment")
        {
            string sComment=p.get(sIndex+".Comment");
            MirrorComment* mc=new MirrorComment(sComment);
            mc->set_when(p.get_long(sIndex+".When"));
            pm->add_item(mc);
        }

        if(sType=="MirrorWork")
        {
            string sWork=p.get(sIndex+".Work");
            MirrorWork* mw=new MirrorWork(sWork);
            mw->set_when(p.get_unsigned_int(sIndex+".When"));
            if(p.exist(sIndex+".Duration"))
                mw->set_duration(p.get_unsigned_int(sIndex+".Duration"));

            if(p.exist(sIndex+".WorkType"))
                mw->set_work_type(p.get_int(sIndex+".WorkType"));

            pm->add_item(mw);
        }

	if( sType == "MirrorUnmaskedMeasure")
	  {
            MirrorUnmaskedMeasure* mum=new MirrorUnmaskedMeasure;
            mum->set_when(p.get_unsigned_int(sIndex+".When"));
            if(p.exist(sIndex+".TotalDiameter"))
                mum->set_mirror_total_diameter
		  ( p.get_double(sIndex+".TotalDiameter"));
            if(p.exist(sIndex+".RGB_channel"))
	      mum->set_RGB_channel
		(p.get_unsigned_int(sIndex+".RGB_channel"));
            if(p.exist(sIndex+".Slit_Angle"))
                mum->set_slit_angle
		  ( p.get_double(sIndex+".Slit_Angle"));

            if(p.exist(sIndex+".Flat_Image"))
                mum->set_flat_image_name
		  ( p.get(sIndex+".Flat_Image"));
            if(p.exist(sIndex+".First_Image"))
                mum->set_first_image_name
		  ( p.get(sIndex+".First_Image"));
	    
            if(p.exist(sIndex+".Number_Images"))
	      mum->set_number_images
		(p.get_unsigned_int(sIndex+".Number_Images"));
            if(p.exist(sIndex+".Delta_Hx"))
                mum->set_delta_hx
		  ( p.get_double(sIndex+".Delta_Hx"));

            if(p.exist(sIndex+".Img_Number_Part_Size"))
	      mum->set_img_name_number_part_size
		(p.get_unsigned_int(sIndex+".Img_Number_Part_Size"));
            if(p.exist(sIndex+".Img_Suffix_Size"))
	      mum->set_img_name_suffix_size
		(p.get_unsigned_int(sIndex+".Img_Suffix_Size"));

	    pm->add_item(mum);
	  }

	
        if(sType=="MirrorCouderMeasure")
        {
            MirrorCouderMeasure* mcm=new MirrorCouderMeasure(pm);
            vector<double> vd=p.get_vector_double(sIndex+".Measure");
            string sAspect; double dMeridian = 0;
            if(p.exist(sIndex+".Measure.Aspect"))
                sAspect=p.get(sIndex+".Measure.Aspect");
            if(p.exist(sIndex+".Measure.Meridian"))
                dMeridian=p.get_double(sIndex+".Measure.Meridian");

	    vector<double> vdHm;
            if(p.exist(sIndex+".UnmaskedHM"))
	      {
		vdHm=p.get_vector_double(sIndex+".UnmaskedHM");
	      }
	    else {
	      vdHm.resize(pm->nb_zones());
	      vdHm[0]=(pm->hole_diameter() + pm->hx()[0])/2.;	    
	      for(unsigned int i=1; i<pm->nb_zones(); i++)
		vdHm[i]= (pm->hx()[i-1] + pm->hx()[i] )/2;
	    }
	    mcm->set_measure(vd, vdHm, sAspect);
	    mcm->set_measure_meridian( dMeridian );
            mcm->set_when(p.get_unsigned_int(sIndex+".When"));
            pm->add_item(mcm);
        }
    }

    pm->initialize();
    return pm;
}
////////////////////////////////////////////////////////////////////////////////
bool MirrorIo::save(Mirror* pm,string sFile)
{
    assert(pm!=0);
    assert(sFile.empty()==false);
    Properties p;

    p.set("Name",pm->name());
    p.set("Diameter",pm->diameter());
    p.set("HoleDiameter",pm->hole_diameter());
    p.set("ObstructionSize",pm->obstruction_size());
    p.set("EdgeMaskWidth",pm->edge_mask_width());
    p.set("Focal",pm->focal());
    p.set("Conical",pm->conical());
    p.set("Hx",pm->hx());
    p.set("MovingLight",pm->is_slit_moving());

    p.set("ShowBothSides",pm->get_show_both_side());
    p.set("SmoothCurves",pm->get_smooth_curves());

    p.set("ShowColors",pm->get_show_colors());
    p.set("DisplayMode",pm->get_display_mode());

    for(int i=0;i<pm->nb_item();i++)
    {
        MirrorItem* mi=pm->get_item(i);
        stringstream ss;
        ss << i;
        string sIndex=ss.str();
        string sType=mi->type();

        p.set(sIndex+".Type",sType);
        p.set(sIndex+".When",mi->when());

        if(sType=="MirrorComment")
        {
            MirrorComment* tc=dynamic_cast<MirrorComment*>(mi);
            p.set(sIndex+".Comment",tc->comment());
        }

        if(sType=="MirrorWork")
        {
            MirrorWork* tc=dynamic_cast<MirrorWork*>(mi);
            p.set(sIndex+".Work",tc->work());
            p.set(sIndex+".Duration",tc->duration());
            p.set(sIndex+".WorkType",tc->work_type());
        }

	if( sType == "MirrorUnmaskedMeasure")
	  {
            MirrorUnmaskedMeasure* mum = dynamic_cast<MirrorUnmaskedMeasure*>(mi);
	    p.set(sIndex+".TotalDiameter", mum->get_mirror_total_diameter());
	    p.set(sIndex+".RGB_channel", mum->get_RGB_channel());
	    p.set(sIndex+".Slit_Angle", mum->get_slit_angle());

	    p.set(sIndex+".Flat_Image", mum->get_flat_image_name());
	    p.set(sIndex+".First_Image", mum->get_first_image_name());
	    
	    p.set(sIndex+".Number_Images", mum->get_number_images());
	    p.set(sIndex+".Delta_Hx", mum->get_delta_hx());
	    p.set(sIndex+".Img_Number_Part_Size", mum->get_img_name_number_part_size());
	    p.set(sIndex+".Img_Suffix_Size", mum->get_img_name_suffix_size());
	  }

        if(sType=="MirrorCouderMeasure")
        {	  
            MirrorCouderMeasure* mcm=dynamic_cast<MirrorCouderMeasure*>(mi);
	    if( mcm->measures().size() != pm->hx().size() )
            p.set(sIndex+".UnmaskedHM",mcm->hmx());	      
            p.set(sIndex+".Measure",mcm->measures());
            p.set(sIndex+".Measure.Aspect",mcm->get_aspect());
            p.set(sIndex+".Measure.Meridian",mcm->measure_meridian());
        }
    }

    return p.save(sFile);
}
////////////////////////////////////////////////////////////////////////////////
Mirror* MirrorIo::import(string sFile)
{
    Properties p;
    if(p.load(sFile)==false)
        return 0;

    Mirror* pm=new Mirror;

    pm->set_name(p.get("Title"));
    pm->set_diameter(p.get_double("D"));
    pm->set_hole_diameter(p.get_double("Hole")*2.); //in old version 1.xx, it was hole radius
    pm->set_focal(p.get_double("Ray")/2.);

    if(p.exist("ConicalConstant"))
        pm->set_conical(p.get_double("ConicalConstant"));
    else
        pm->set_conical(-1.);

    if(p.exist("ShowBothSides"))
        pm->set_show_both_side(p.get_bool("ShowBothSides"));
    else
        pm->set_show_both_side(true);

    if(p.exist("SmoothCurves"))
        pm->set_smooth_curves(p.get_bool("SmoothCurves"));
    else
        pm->set_smooth_curves(false);

    pm->set_show_colors(true);
    pm->set_display_mode(1);

    // lit les hx
    vector<double> vdhx=p.get_vector_double("Hx");
    pm->set_hx(vdhx);
    pm->set_is_slit_moving(p.get_int("MovingLight")!=0);

    pm->initialize();
    int iIndex=0;
    bool bFound=true;
    while(bFound)
    {
        stringstream ss;
        ss << iIndex;
        string sIndex=ss.str();

        // lit la mesure iIndex
        bFound=p.exist("Measure"+sIndex);
        if(!bFound) continue;
	
        MirrorCouderMeasure* mcm=new MirrorCouderMeasure(pm);
        vector<double> vdmes=p.get_vector_double("Measure"+sIndex);
        string sAspect;
        if(p.exist("Aspect"+sIndex))
	  sAspect=p.get("Aspect"+sIndex);

	vector<double> vdHm;
	vdHm.resize(pm->nb_zones());
	vdHm[0]=(pm->hole_diameter() + pm->hx()[0])/2.;	    
	for(unsigned int i=1; i<pm->nb_zones(); i++)
	  vdHm[i]= (pm->hx()[i-1] + pm->hx()[i] )/2;

	mcm->set_measure(vdmes, vdHm, sAspect);

        pm->add_item(mcm);

        // lit le comment iIndex : warning, it is a work in version 1
        bFound=p.exist("Comment"+sIndex);
        if(!bFound) continue;

        string sComment=p.get("Comment"+sIndex);

        if(!sComment.empty())
        {
            MirrorWork* mc=new MirrorWork(sComment); // added as work
            pm->add_item(mc);
        }
        iIndex++;
    }

    pm->initialize();
    return pm;
}
////////////////////////////////////////////////////////////////////////////////
