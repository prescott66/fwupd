fwupd
=====

fwupd is a simple daemon to allow session software to update device firmware on
your local machine. It's designed for desktops, but this project is probably
quite interesting for phones, tablets and server farms, so I'd be really happy
if this gets used on other non-desktop hardware.

You can either use a GUI software manager like GNOME Software to view and apply
updates, the command-line tool or the system D-Bus interface directly.

Introduction
------------

Updating firmware easily is actually split into two parts:

 * Providing metadata about what vendor updates are available (AppStream)
 * A mechanism to actually apply the file onto specific hardware (this project)

What do we actually need to apply firmware easily? A raw binary firmware file
isn't so useful, and so Microsoft have decided we should all package it up in a
.cab file (a bit like a .zip file) along with a .inf file that describes the
update in more detail. The .inf file gives us the hardware ID of what the
firmware is referring to, as well as the vendor and a short update description.

So far the update descriptions have been less than awesome so we also need some
way of fixing up some of the update descriptions to be suitable to show the user.

I'm asking friendly upstream vendors to start shipping a MetaInfo file alongside
the .inf file in the firmware .cab file. This means we can have fully localized
update descriptions, along with all the usual things you'd expect from an
update, e.g. the upstream vendor, the licensing information, etc.

Of course, a lot of vendors are not going to care about good descriptions, and
won't be interested in shipping another file in the update just for Linux users.
For that, we can actually "inject" a replacement MetaInfo file when we curate
the AppStream metadata. This allows us to download all the .cab files we care
about, but are not allowed to redistribute, run the `appstream-builder` on them,
then package up just the XML metadata which can be consumed by pretty much any
distribution tool.

A lot of people don't have UEFI hardware that is capable of applying capsule
firmware updates, so I've also added a ColorHug provider, which predictably also
lets you update the firmware on your ColorHug device. It's a lot lower risk
testing all this code with a £20 device than your nice shiny expensive prototype
hardware.

I'm also happy to accept patches for other hardware that supports updates,
although the internal API isn't 100% stable yet. The provider concept allows
vendors to do pretty much anything to get the list of attached hardware, as long
as a unique hardware component is in some way mapped to a GUID value.
Ideally the tools would be open source, or better still not needing any external
tools at all. Reading a VID/PID and then writing firmware to a chip usually
isn't rocket science.

What is standardised is the metadata, using AppStream 0.9 as the interchange
format. A lot of tools already talk AppStream and so this makes working with
other desktop and server tools very easy. Actually generating the AppStream
metadata can either be done using using `appstream-builder`, or some random
vendor-specific non-free Perl/C++/awk script that operates on internal data;
the point is that as long as the output format is AppStream and the metadata
GUID matches the hardware GUID we don't really care.

Security
--------

By default, any users are able to install firmware to removable hardware.
The logic here is that if the hardware can be removed, it can easily be moved to
a device that the user already has root access on, and asking for authentication
would just be security theatre.

For non-removable devices, e.g. UEFI firmware, admin users are able to update
firmware without the root password. By default, we already let admin user and
root update glibc and the kernel without additional authentication, and these
would be a much easier target to backdoor. The firmware updates themselves
have a checksum, and the metadata describing this checksum is provided by the
distribution either as GPG-signed repository metadata, or installed from a
package, which is expected to also be signed. It is important that clients that
are downloading firmware for fwupd check the checksum before asking fwupd to
update a specific device.

User Interaction
----------------

No user interaction should be required when actually applying updates. Making
it prohibited means we can do the upgrade with a fancy graphical splash screen,
without having to worry about locales and input methods. Updating firmware
should be no more dangerous than installing a new kernel or glibc package.

Offline Updates Lifecycle
-------------------------

Offline updates are done using a special boot target which means that the usual
graphical environment is not started. Once the firmware update has completed the
system will reboot.

Devices go through the following lifecycles:

 * created -> `SCHEDULED` -> `SUCCESS` -> deleted
 * created -> `SCHEDULED` -> `FAILED` -> deleted

Any user-visible output is available using the `GetResults()` D-Bus method, and
the database entry is only deleted once the `ClearResults()` method is called.

The results are obtained and cleared either using a provider-supplied method
or using a small SQLite database located at `/var/lib/fwupd/pending.db`

ColorHug Support
----------------

You need to install colord 1.2.9 which may be newer that your distribution
provides. Compile it from source https://github.com/hughsie/colord or grab the
RPMS here http://people.freedesktop.org/~hughsient/fedora/

If you don't want or need this functionality you can use `--disable-colorhug`

UEFI Support
------------

If you're wondering where to get fwupdate from, either compile it form source
(you might also need a newer efivar) from https://github.com/rhinstaller/fwupdate
or grab the RPMs here https://pjones.fedorapeople.org/fwupdate/

If you don't want or need this functionality you can use `--disable-uefi`
