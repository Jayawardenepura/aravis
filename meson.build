project ('aravis', 'c', 'cpp', version: '0.8.7', meson_version: '>=0.47.0')

gnome = import('gnome')
pkg = import ('pkgconfig')

aravis_version = meson.project_version ()
aravis_api_version = '0.8'

versions = aravis_version.split ('.')
aravis_major_version = versions[0].to_int ()
aravis_minor_version = versions[1].to_int ()
aravis_micro_version = versions[2].to_int ()

aravis_data_dir = join_paths (get_option ('datadir'), 'aravis-@0@'.format (aravis_api_version))

cc = meson.get_compiler ('c')

if cc.get_id()=='gcc'
  warning_c_args = [
    '-Wduplicated-branches',
    '-Wimplicit-fallthrough',
    '-Wmisleading-indentation',
    '-Wstrict-prototypes',
    '-Wunused',
    '-Wdeclaration-after-statement',
    '-Wformat=2',
    '-Wimplicit-function-declaration',
    '-Winit-self',
    '-Wmissing-include-dirs',
    '-Wmissing-prototypes',
    '-Wpointer-arith',
    '-Wformat-nonliteral',
    '-Wenum-conversion'
    ]

  add_project_arguments(cc.get_supported_arguments(warning_c_args), language: 'c')
endif

gobject_dep = dependency ('gobject-2.0', required: true)
gio_dep = dependency ('gio-2.0', required: true)
xml2_dep = dependency ('libxml-2.0', required: true)
libz_dep = dependency ('zlib', required: true)
thread_dep = dependency('threads', required: true)

libm = cc.find_library ('m', required: true)

aravis_public_dependencies = [gobject_dep, gio_dep, thread_dep]
aravis_dependencies = [aravis_public_dependencies, xml2_dep, libz_dep, libm]

has_if_packet = cc.has_header (join_paths ('linux','if_packet.h'))
packet_socket_option = get_option('packet-socket')
if packet_socket_option.enabled()
  if not has_if_packet
    error ('missing header for packet-socket support')
  endif
  packet_socket_enabled = true
else
  packet_socket_enabled = has_if_packet and packet_socket_option.auto()
endif

subdir ('src')
subdir ('tests')
