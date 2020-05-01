#! /usr/local/env python

import sys

class BasePlatformConfig:
	def __init__(self):
		self.defines = []
		self.cxxflags = []
		self.linkflags = []

	def union(self, other):
		self.defines += other.defines
		self.cxxflags += other.cxxflags
		self.linkflags += other.linkflags

	def export(self, ctx):
		ctx.env.append_unique("DEFINES", self.defines)
		ctx.env.append_unique("CXXFLAGS", self.cxxflags)
		ctx.env.append_unique("LINKFLAGS", self.linkflags)

class MatchableConfig(BasePlatformConfig):
	def __init__(self, platform=None, buildType=None, compiler=None, defines=[], cxxflags=[], linkflags=[]):
		super().__init__()
		self.platform = platform
		self.buildType = buildType
		self.compiler = compiler

		self.defines += defines
		self.cxxflags += cxxflags
		self.linkflags += linkflags

	def description(self):
		components = \
		[
			self.__description("platform", self.platform),
			self.__description("buildType", self.buildType),
			self.__description("compiler", self.compiler)
		]

		return " AND ".join([item for item in components if item is not None])

	def matches(self, ctx):
		return self.__matches(self.platform, sys.platform) and \
			   self.__matches(self.buildType, ctx.env.BUILD_TYPE) and \
			   self.__matches(self.compiler, ctx.env.CXX_NAME)

	def __description(self, propName, propValue):
		if propValue is None:
			return None

		matchType = " = "
		toMatch = ""

		if isinstance(propValue, tuple):
			toMatch = propValue[0]

			if not propValue[1]:
				matchType = " != "
		else:
			toMatch = propValue

		return propName + matchType + toMatch

	def __matches(self, prop, compareValue):
		if prop is None:
			# Always matches.
			return True
		if isinstance(prop, tuple):
			# If the second item in the tuple is False, the match is inverted.
			match = prop[0] == compareValue
			return match if prop[1] else not match
		else:
			# Straightforward match.
			return prop == compareValue

APPNAME = "nfconsole-reversebin"

SUBDIRS = \
[
	"binanalyser"
]

CONFIGS = \
[
	MatchableConfig(
		buildType="debug",
		defines=["DEBUG"]
	),

	MatchableConfig(
		compiler="msvc",
		cxxflags=["/EHsc"]
	),

	MatchableConfig(
		platform="windows",
		defines=[r'PATH_SEP="\\"']
	),

	MatchableConfig(
		platform=("windows", False),
		defines=['PATH_SEP="/"']
	)
]

def options(ctx):
	ctx.load("compiler_cxx")

	ctx.add_option('--build-type',
				   action='store',
				   type='string',
				   dest='BUILD_TYPE',
				   default = "release",
				   help = 'Build type: release (default) or debug.')

	ctx.recurse(SUBDIRS)

def configure(ctx):
	ctx.load("compiler_cxx")

	ctx.env.BUILD_TYPE = "debug" if ctx.options.BUILD_TYPE == "debug" else "release"
	ctx.msg("Build type:", ctx.env.BUILD_TYPE, color="GREEN")

	config = BasePlatformConfig()

	for item in CONFIGS:
		if item.matches(ctx):
			ctx.msg("Using config:", item.description(), color="BLUE")
			config.union(item)

	config.export(ctx)
	ctx.recurse(SUBDIRS)

def build(bld):
	bld.install_files("${PREFIX}/files",
					  bld.path.ant_glob("bin/**/*.*"),
					  relative_trick=True)

	bld.recurse(SUBDIRS)
