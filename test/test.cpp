			if(closest.face != nullptr)
			{
				Vector3D normale = closest.face->normal;
				Color faceCol;
				if(normale.getY() > fabs(normale.getZ()) && normale.getY() > fabs(normale.getX())){
					// std::cout << normale << std::endl;
					//Farbwert der Fläche am HP berechen
					size_t colXpos = wPixelsPerWorldUint * (closest.position.getX() + sceneWidthForText / 2);
					size_t colZpos = hPixelsPerWorldUint * (sceneHeightForText/2 - closest.position.getZ());
					faceCol = texture[0].get(colXpos, colZpos);
				}else{
					faceCol = Color(255,255,255);
				}

				for(Light l : this->lights){
					Vector3D lightSource = l.getLightSource();
					Vector3D path = closest.position - lightSource;
					Vector3D lightDirection = Vector3D::normalize(path) * -1.0f;
					Ray LightRay = Ray(lightSource, path);

					Hitpoint LightHit = this->disect->closestHitpoint(LightRay);

					if(LightHit.position == closest.position){
						//std::cout << " Hit" << std::endl;
						//col = closest.face->texture.color;

						float dot = Vector3D::dot(lightDirection, normale);
						float intensity = std::max(dot, 0.0f) * (1.0f / (LightHit.distance / l.fallof() + 1.0f));
						//std::cout << dot << std::endl;


						col += l.getColor().on(faceCol) * intensity; // theoretisch kommt hier noch lichtfarbe aber so ists halt 1 aka weißes licht
						//col += closest.face->texture.color * intensity;

						//col = closest.face->texture.color;s
						
						/*Vector3D vec  = closest.face->normal;
						vec = Vector3D::normalize(vec);
						col = Color(255 * vec.getX(), 255*vec.getY(), 255*vec.getZ());*/
					}	
				}
			}
