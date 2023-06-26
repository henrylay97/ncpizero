const SpillVar kPrintEvent([](const caf::SRSpillProxy *sp) -> double {
    std::cerr << sp->hdr.run << " " << sp->hdr.subrun << " " << sp->hdr.evt << std::endl;

    return 0.5;
  });
