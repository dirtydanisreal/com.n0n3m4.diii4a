/*
 * Copyright (C) 2012  Oliver McFadden <omcfadde@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#version 300 es
#pragma optimize(off)

precision mediump float;

in vec3 attr_Bitangent;
in vec3 attr_Normal;
in vec3 attr_Tangent;
in lowp vec4 attr_Color;
in vec4 attr_TexCoord;
in highp vec4 attr_Vertex;

uniform highp mat4 u_modelViewProjectionMatrix;

void main(void)
{
	//gl_Position = ftransform();
	gl_Position = u_modelViewProjectionMatrix * attr_Vertex;
}
