/*************************************************************************
 *                                                                       *
 * Open Dynamics Engine, Copyright (C) 2001,2002 Russell L. Smith.       *
 * All rights reserved.  Email: russ@q12.org   Web: www.q12.org          *
 *                                                                       *
 * This library is free software; you can redistribute it and/or         *
 * modify it under the terms of EITHER:                                  *
 *   (1) The GNU Lesser General Public License as published by the Free  *
 *       Software Foundation; either version 2.1 of the License, or (at  *
 *       your option) any later version. The text of the GNU Lesser      *
 *       General Public License is included with this library in the     *
 *       file LICENSE.TXT.                                               *
 *   (2) The BSD-style license that is included with this library in     *
 *       the file LICENSE-BSD.TXT.                                       *
 *                                                                       *
 * This library is distributed in the hope that it will be useful,       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the files    *
 * LICENSE.TXT and LICENSE-BSD.TXT for more details.                     *
 *                                                                       *
 *************************************************************************/

#include <vector>
#include <ode/ode.h>
#include <drawstuff/drawstuff.h>
#include "texturepath.h"
#include <unordered_map>
using namespace std;

#ifdef dDOUBLE
#define dsDrawBox dsDrawBoxD
#endif

static dSpaceID space;
static dWorldID world;
static dJointGroupID contactgroup;

vector<unordered_map<dGeomID, int>> no_collision_groups;

//Gernerated by Armature
static dBodyID body_ball1;
static dGeomID geom_ball1;
//Gernerated by Armature
static dBodyID body_ball2;
static dGeomID geom_ball2;
//Gernerated by Armature
static dBodyID body_box1;
static dGeomID geom_box1;
const float sides_box1[3] = { 1, 1, 1 };
//Gernerated by Armature
static dBodyID body_asdf;
static dGeomID geom_asdf;
const float sides_asdf[3] = { 1, 1, 1 };
//Gernerated by Armature
static dBodyID body_box3;
static dGeomID geom_box3;
const float sides_box3[3] = { 1, 1, 1 };
//Gernerated by Armature
static dBodyID body_box4;
static dGeomID geom_box4;
const float sides_box4[3] = { 1, 1, 1 };
//Gernerated by Armature
static dBodyID body_fdafa;
static dGeomID geom_fdafa;
const float sides_fdafa[3] = { 5, 5, 5 };


void start()
{
	puts("Controls:");
	puts("   SPACE - reset bodies");
}

static void reset_bodies(void)
{
	
	//Generated by Armature
	dQuaternion qball1;
	dQSetIdentity(qball1);
	dBodySetPosition(body_ball1, 1.0f, -0.5f, 10.0f);
	dBodySetQuaternion(body_ball1, qball1);
	dBodySetLinearVel(body_ball1, 0, 0, 0);
	dBodySetAngularVel(body_ball1, 0, 0, 0);
	
	//Generated by Armature
	dQuaternion qball2;
	dQSetIdentity(qball2);
	dBodySetPosition(body_ball2, 1.0f, 0.5f, 10.0f);
	dBodySetQuaternion(body_ball2, qball2);
	dBodySetLinearVel(body_ball2, 0, 0, 0);
	dBodySetAngularVel(body_ball2, 0, 0, 0);
	
	//Generated by Armature
	dBodySetPosition(body_box1, -1.0, 0.5, 6.0);
	dBodySetLinearVel(body_box1, 0, 0, 0);
	dBodySetAngularVel(body_box1, 0, 0, 0);

	//Generated by Armature
	dBodySetPosition(body_asdf, -1.0, -0.5, 5.0);
	dBodySetLinearVel(body_asdf, 0, 0, 0);
	dBodySetAngularVel(body_asdf, 0, 0, 0);

	//Generated by Armature
	dBodySetPosition(body_box3, 1.0, 0.5, 6.0);
	dBodySetLinearVel(body_box3, 0, 0, 0);
	dBodySetAngularVel(body_box3, 0, 0, 0);

	//Generated by Armature
	dBodySetPosition(body_box4, 1.0, -0.5, 5.0);
	dBodySetLinearVel(body_box4, 0, 0, 0);
	dBodySetAngularVel(body_box4, 0, 0, 0);

	//Generated by Armature
	dBodySetPosition(body_fdafa, 1.0, -0.5, 20.0);
	dBodySetLinearVel(body_fdafa, 0, 0, 0);
	dBodySetAngularVel(body_fdafa, 0, 0, 0);

}

static void nearCallback(void *, dGeomID o1, dGeomID o2)
{
	// exit without doing anything if the two bodies are connected by a joint
	dBodyID b1 = dGeomGetBody(o1);
	dBodyID b2 = dGeomGetBody(o2);

	//Uncomment if you don't want connected objects to hit eachother.
	//if (b1 && b2 && dAreConnected (b1,b2)) return;

	const int MAX_CONTACTS = 8;
	dContact contact[MAX_CONTACTS];

	int numc = dCollide(o1, o2, MAX_CONTACTS,
		&contact[0].geom,
		sizeof(dContact));

	for (int i = 0; i < numc; i++) {
		contact[i].surface.mode = dContactSoftERP | dContactSoftCFM | dContactApprox1 | dContactSlip1 | dContactSlip2;
		contact[i].surface.mu = 50.0; // was: dInfinity
		contact[i].surface.soft_erp = 0.96;
		contact[i].surface.soft_cfm = 2.00;
		dJointID c = dJointCreateContact(world, contactgroup, contact + i);
		dJointAttach(c, b1, b2);
	}
}

void simLoop(int pause)
{
	if (!pause) {
		dSpaceCollide(space, 0, &nearCallback);
		dWorldQuickStep(world, 0.01);
		dJointGroupEmpty(contactgroup);
	}

	
	//Generated by Armature
	dsSetColor(0, 0, 1);
	const dReal *SPos_ball1 = dBodyGetPosition(body_ball1);
	const dReal *SRot_ball1 = dBodyGetRotation(body_ball1);
	float spos_ball1[3] = { SPos_ball1[0], SPos_ball1[1], SPos_ball1[2] };
	float srot_ball1[12] = { SRot_ball1[0], SRot_ball1[1], SRot_ball1[2], SRot_ball1[3], SRot_ball1[4], SRot_ball1[5], SRot_ball1[6], SRot_ball1[7], SRot_ball1[8], SRot_ball1[9], SRot_ball1[10], SRot_ball1[11] };
	dsDrawSphere
	(
		spos_ball1,
		srot_ball1,
		1.0
	);
	
	//Generated by Armature
	dsSetColor(1, 1, 0);
	const dReal *SPos_ball2 = dBodyGetPosition(body_ball2);
	const dReal *SRot_ball2 = dBodyGetRotation(body_ball2);
	float spos_ball2[3] = { SPos_ball2[0], SPos_ball2[1], SPos_ball2[2] };
	float srot_ball2[12] = { SRot_ball2[0], SRot_ball2[1], SRot_ball2[2], SRot_ball2[3], SRot_ball2[4], SRot_ball2[5], SRot_ball2[6], SRot_ball2[7], SRot_ball2[8], SRot_ball2[9], SRot_ball2[10], SRot_ball2[11] };
	dsDrawSphere
	(
		spos_ball2,
		srot_ball2,
		1.0
	);
	
	//Generated by Armature
	dsSetColor(1, 1, 0);
	dsDrawBox(dBodyGetPosition(body_box1),
		dBodyGetRotation(body_box1), sides_box1);

	//Generated by Armature
	dsSetColor(0, 0, 1);
	dsDrawBox(dBodyGetPosition(body_asdf),
		dBodyGetRotation(body_asdf), sides_asdf);

	//Generated by Armature
	dsSetColor(0, 0, 1);
	dsDrawBox(dBodyGetPosition(body_box3),
		dBodyGetRotation(body_box3), sides_box3);

	//Generated by Armature
	dsSetColor(1, 1, 0);
	dsDrawBox(dBodyGetPosition(body_box4),
		dBodyGetRotation(body_box4), sides_box4);

	//Generated by Armature
	dsSetColor(1, 0, 0);
	dsDrawBox(dBodyGetPosition(body_fdafa),
		dBodyGetRotation(body_fdafa), sides_fdafa);

}

void command(int c)
{
	switch (c) {
	case ' ':
		reset_bodies();
		break;
	}
}

int main(int argc, char **argv)
{
	dMass m;

	dInitODE();

	// setup pointers to drawstuff callback functions
	dsFunctions fn;
	fn.version = DS_VERSION;
	fn.start = &start;
	fn.step = &simLoop;
	fn.command = &command;
	fn.stop = 0;
	fn.path_to_textures = DRAWSTUFF_TEXTURE_PATH;

	//Create world
	world = dWorldCreate();
	dWorldSetGravity(world, 0, 0, -0.98);
	dWorldSetQuickStepNumIterations(world, 50); // <-- increase for more stability

	//Create 'ground'
	space = dSimpleSpaceCreate(0);
	contactgroup = dJointGroupCreate(0);
	dGeomID ground = dCreatePlane(space, 0, 0, 1, 0);

	
	//Generated by Armature
	//Create Sphere_ball1
	body_ball1 = dBodyCreate(world);
	dMassSetSphere(&m, 1, 1.0);
	dBodySetMass(body_ball1, &m);
	geom_ball1 = dCreateSphere(0, 1.0);
	dGeomSetBody(geom_ball1, body_ball1);
	dBodySetPosition(body_ball1, 1.0f, -0.5f, 10.0f);
	dSpaceAdd(space, geom_ball1);
	
	//Generated by Armature
	//Create Sphere_ball2
	body_ball2 = dBodyCreate(world);
	dMassSetSphere(&m, 1, 1.0);
	dBodySetMass(body_ball2, &m);
	geom_ball2 = dCreateSphere(0, 1.0);
	dGeomSetBody(geom_ball2, body_ball2);
	dBodySetPosition(body_ball2, 1.0f, 0.5f, 10.0f);
	dSpaceAdd(space, geom_ball2);
	
	//Generated by Armature
	//Create Box_box1
	body_box1 = dBodyCreate(world);
	geom_box1 = dCreateBox(0, 1, 1, 1);
	dGeomSetBody(geom_box1, body_box1);
	m.setBox(1, 1,1,1);
	dBodySetMass(body_box1, &m);
	dBodySetPosition(body_box1, -1.0, 0.5, 6.0);
	dSpaceAdd(space, geom_box1);

	//Generated by Armature
	//Create Box_asdf
	body_asdf = dBodyCreate(world);
	geom_asdf = dCreateBox(0, 1, 1, 1);
	dGeomSetBody(geom_asdf, body_asdf);
	m.setBox(1, 1,1,1);
	dBodySetMass(body_asdf, &m);
	dBodySetPosition(body_asdf, -1.0, -0.5, 5.0);
	dSpaceAdd(space, geom_asdf);

	//Generated by Armature
	//Create Box_box3
	body_box3 = dBodyCreate(world);
	geom_box3 = dCreateBox(0, 1, 1, 1);
	dGeomSetBody(geom_box3, body_box3);
	m.setBox(1, 1,1,1);
	dBodySetMass(body_box3, &m);
	dBodySetPosition(body_box3, 1.0, 0.5, 6.0);
	dSpaceAdd(space, geom_box3);

	//Generated by Armature
	//Create Box_box4
	body_box4 = dBodyCreate(world);
	geom_box4 = dCreateBox(0, 1, 1, 1);
	dGeomSetBody(geom_box4, body_box4);
	m.setBox(1, 1,1,1);
	dBodySetMass(body_box4, &m);
	dBodySetPosition(body_box4, 1.0, -0.5, 5.0);
	dSpaceAdd(space, geom_box4);

	//Generated by Armature
	//Create Box_fdafa
	body_fdafa = dBodyCreate(world);
	geom_fdafa = dCreateBox(0, 5, 5, 5);
	dGeomSetBody(geom_fdafa, body_fdafa);
	m.setBox(1, 1,1,1);
	dBodySetMass(body_fdafa, &m);
	dBodySetPosition(body_fdafa, 1.0, -0.5, 20.0);
	dSpaceAdd(space, geom_fdafa);


	//Generated by Armature
	dJointID ball_joint_2 = dJointCreateBall(world, 0);
	dJointAttach(ball_joint_2, body_ball1, body_ball2);
	dJointSetBallAnchor(ball_joint_2, 1.0, 0.0, 10.0);
	//Generated by Armature
	dJointID ball_joint_1 = dJointCreateBall(world, 0);
	dJointAttach(ball_joint_1, body_box1, body_asdf);
	dJointSetBallAnchor(ball_joint_1, -1.0, 0.0, 5.5);
	//Generated by Armature
	dJointID ball_joint_3 = dJointCreateBall(world, 0);
	dJointAttach(ball_joint_3, body_box3, body_box4);
	dJointSetBallAnchor(ball_joint_3, 1.0, 0.0, 5.5);
	

	//Generated by Armature
	unordered_map<dGeomID, int> no_collision_map0;
	no_collision_map0[geom_box1] = 0;
	no_collision_map0[geom_asdf] = 0;
	
	no_collision_groups.push_back(no_collision_map0);
//Generated by Armature
	unordered_map<dGeomID, int> no_collision_map1;
	no_collision_map1[geom_box3] = 0;
	no_collision_map1[geom_box4] = 0;
	
	no_collision_groups.push_back(no_collision_map1);


	reset_bodies();

	// run simulation
	dsSimulationLoop(argc, argv, 640, 480, &fn);

	dJointGroupDestroy(contactgroup);
	dWorldDestroy(world);
	dGeomDestroy(ground);
	dSpaceDestroy(space);

	dCloseODE();
}