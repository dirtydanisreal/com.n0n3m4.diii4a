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
//#pragma optimize(off)

precision mediump float;

uniform sampler2D u_fragmentMap0;
uniform lowp vec4 u_glColor;

in vec2 var_TexDiffuse;
in lowp vec4 var_Color;

out vec4 _gl_FragColor;

void main(void)
{
	_gl_FragColor = texture(u_fragmentMap0, var_TexDiffuse) * u_glColor * var_Color;
}
