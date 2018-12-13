# echo "cleanup BesEvtGen BesEvtGen-00-03-98 in /afs/.ihep.ac.cn/bes3/offline/Boss/7.0.4/Generator"

if test "${CMTROOT}" = ""; then
  CMTROOT=/afs/ihep.ac.cn/bes3/offline/ExternalLib/SLC6/contrib/CMT/v1r25; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh
cmtBesEvtGentempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if test ! $? = 0 ; then cmtBesEvtGentempfile=/tmp/cmt.$$; fi
${CMTROOT}/mgr/cmt cleanup -sh -pack=BesEvtGen -version=BesEvtGen-00-03-98 -path=/afs/.ihep.ac.cn/bes3/offline/Boss/7.0.4/Generator  $* >${cmtBesEvtGentempfile}
if test $? != 0 ; then
  echo >&2 "${CMTROOT}/mgr/cmt cleanup -sh -pack=BesEvtGen -version=BesEvtGen-00-03-98 -path=/afs/.ihep.ac.cn/bes3/offline/Boss/7.0.4/Generator  $* >${cmtBesEvtGentempfile}"
  cmtcleanupstatus=2
  /bin/rm -f ${cmtBesEvtGentempfile}
  unset cmtBesEvtGentempfile
  return $cmtcleanupstatus
fi
cmtcleanupstatus=0
. ${cmtBesEvtGentempfile}
if test $? != 0 ; then
  cmtcleanupstatus=2
fi
/bin/rm -f ${cmtBesEvtGentempfile}
unset cmtBesEvtGentempfile
return $cmtcleanupstatus

