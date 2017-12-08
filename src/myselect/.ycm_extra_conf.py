def FlagsForFile( filename, **kwargs ):
  return {
    'flags': [ '-x', 'c', '-I../../include/', '-Wall', '-Werror', '--pedantic' ],
  }
