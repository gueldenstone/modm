#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Copyright (c) 2009, Roboterclub Aachen e.V.
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
# 
#  * Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#  * Neither the name of the Roboterclub Aachen e.V. nor the
#    names of its contributors may be used to endorse or promote products
#    derived from this software without specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY ROBOTERCLUB AACHEN E.V. ''AS IS'' AND ANY
# EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL ROBOTERCLUB AACHEN E.V. BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
# THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# 
# $Id$
# -----------------------------------------------------------------------------

import os

env = Environment(tools = ['template', 'doxygen', 'configparser'], toolpath = ['misc/python/scons'])

# -----------------------------------------------------------------------------
# regenerate SConstruct files for the tests
parser = env.ConfigParser()
for path, directories, files in os.walk('tests'):
	# exclude the SVN-directories
	if '.svn' in directories:
		directories.remove('.svn')
	
	if 'project.cfg' in files:
		parser.read(os.path.join(path, 'project.cfg'))
		
		rootpath = os.sep.join(['..' for x in range(len(path.split(os.sep)))])
		file = env.SimpleTemplate(target = os.path.join(path, 'SConstruct'),
								  source = 'misc/templates/SConstruct.in',
								  SUBSTITUTIONS = {'rootpath': rootpath })
		
		env.Alias('update', file)

# -----------------------------------------------------------------------------
# update all template files
path = 'src/xpcc/architecture/atmega/uart'
for id in range(0, 4):
	file = env.Template(target = os.path.join(path, 'uart%i.hpp' % id),
						source = os.path.join(path, 'uart.hpp.in'),
						SUBSTITUTIONS = { 'id': id })
	env.Alias('templates', file)
	
	file = env.Template(target = os.path.join(path, 'uart%i.cpp' % id),
						source = os.path.join(path, 'uart.cpp.in'),
						SUBSTITUTIONS = { 'id': id })
	env.Alias('templates', file)

# -----------------------------------------------------------------------------
# update more template files
path = 'src/xpcc/architecture/atxmega/uart'
for id in ['D0', 'D1', 'C0', 'C1']:
	file = env.Template(target = os.path.join(path, 'uart%s.hpp' % id),
						source = os.path.join(path, 'uart.hpp.in'),
						SUBSTITUTIONS = { 'id': id })
	env.Alias('templates', file)
	
	file = env.Template(target = os.path.join(path, 'uart%s.cpp' % id),
						source = os.path.join(path, 'uart.cpp.in'),
						SUBSTITUTIONS = { 'id': id })
	env.Alias('templates', file)

# -----------------------------------------------------------------------------
# add target to create the doxygen documentation
env.Doxygen('doc/doxyfile')
env.Alias('doc', 'apidoc/html')

env.Alias('all', ['update', 'templates', 'doc'])
env.Default('update')
